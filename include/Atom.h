#pragma once

#include <mutex>
#include <functional>

namespace Concurrent
{

/**
 * Atoms provide a way to manage shared, synchronous, independent state.
 *
 * An atom is basically a data abstraction with built-in read and write locks.
 * At any time a copy of the current value can be safely obtained. Writing
 * a new value will block simultaneous reads and writes, thus ensuring
 * thread safety and data integrity.
 *
 * An atom is created with an initial value and an optional validation
 * lambda. At any time the value of the atom can be synchronously and safely
 * changed. If a validator is given at construction then any new value
 * will be checked against the validator and will be rejected if the
 * validator returns false.
 *
 * There are several ways to change the value of an atom: CompareAndSet(),
 * Reset(), and Swap(). The differences relate to how the new value is
 * calculated and how aggressively the atom is locked.
 *
 * @see http://clojure.org/atoms Clojure Atoms
 * @see http://clojure.org/state Values and Change - Clojure's approach to Identity and State
 */
template<typename T>
class Atom
{
public:

  /**
   * A function used to calculate the new value based on the current value.
   *
   * @param currentValue The current value.
   * @return The new value which will be validated and possibly saved.
   */
  typedef std::function<T(const T& currentValue)> UpdateFunc;

  /**
   * A function for validating the new value.
   *
   * @param newValue The new value.
   * @return `true` if the new value is valid else `false`.
   **/
  typedef std::function<bool(const T& newValue)> ValidateFunc;

  /**
   * Constructs a new Atom with the given initial value and optional
   * validation function.
   *
   * @param initialValue The initial value.
   * @param validator Function to be used when validating a new value.
   */
  explicit Atom(const T& initialValue, ValidateFunc validator = [](const T&){ return true; })
    : mValue(initialValue)
    , mValidator(validator)
    {
    }

  virtual ~Atom() {  }

  /**
   * Safely obtain a copy of the current value.
   *
   * @return The current value.
   */
  T Value()
  {
    std::lock_guard<std::mutex> rlock(mReadMutex);
    return mValue;
  }

  /**
   * Atomically sets the value of atom to the new value if and only if the
   * current value of the atom is identical to the old value and the new
   * value successfully validates against the (optional) validator given
   * at construction.
   *
   * @param oldValue The expected current value.
   * @param newValue The intended new value.
   *
   * @return `true` if the value is changed else `false`.
   */
  bool CompareAndSet(const T& oldValue, const T& newValue)
  {
    std::lock_guard<std::mutex> rlock(mReadMutex);
    std::lock_guard<std::mutex> wlock(mWriteMutex);

    if (mValue == oldValue && mValidator(newValue))
    {
      mValue = newValue;
      return true;
    }
    else
    {
      return false;
    }
  }

  /**
   * Atomically sets the value of atom to the new value without regard for the
   * current value so long as the new value successfully validates against the
   * (optional) validator given at construction.
   *
   * @param newValue The intended new value.
   *
   * @return The final value of the atom after all operations and
   *         validations are complete.
   */
  T Reset(const T& newValue)
  {
    std::lock_guard<std::mutex> rlock(mReadMutex);
    std::lock_guard<std::mutex> wlock(mWriteMutex);

    if (mValidator(newValue))
    {
      mValue = newValue;
    }

    return mValue;
  }

  /**
   * Atomically sets the value of atom using the given block. The current
   * value will be passed to the block and thehe new value will be validated
   * against the (optional) validator proc given at construction. If validation
   * fails the value will not be changed.
   *
   * This method locks much more aggressively than Swap() but guarantees that
   * the update function will be run only once.
   *
   * The write lock will be set immediately when this method is called. This
   * lock will prevent other callers from reading the value while the update
   * function is running. This may be very inefficient in cases where the
   * update function runs for a long time. Use Swap() when there is a need to
   * keep the amount of time spent in the write lock to a minium.
   *
   * @param func The lambda used to calculate the new value.
   * @return The current value after the update has occurred (or been rejected
   *         as invalid).
   */
  T Reset(UpdateFunc func)
  {
    std::lock_guard<std::mutex> rlock(mReadMutex);
    std::lock_guard<std::mutex> wlock(mWriteMutex);

    T newValue = func(mValue);

    if (mValidator(newValue))
    {
      mValue = newValue;
    }

    return mValue;
  }

  /**
   * Atomically sets the value of atom using the given block. The current
   * value will be passed to the block and thehe new value will be validated
   * against the (optional) validator proc given at construction. If validation
   * fails the value will not be changed.
   *
   * This method locks much less aggressively than Reset() but the update
   * lambda may be run more than once. Therefore the update lambda should be
   * free of side effects.
   *
   * Since a write lock also blocks readers, this method aggressively seeks to
   * minimize the length of time in the write lock. Internally it reads the
   * current value, applies the block to it, and attempts to CompareAndSet() it
   * in. Since another thread may have changed the value in the intervening time
   * it may have to retry, and does so in a spin loop. The net effect is that
   * the value will always be the result of the application of the supplied
   * lambda to the current value, atomically. However, because the lambda may be
   * called multiple times, it must be free of side effects.
   *
   * @param func The lambda used to calculate the new value.
   * @return The current value after the update has occurred (or been rejected
   *         as invalid).
   */
  T Swap(UpdateFunc func)
  {
    T oldValue, newValue;

    for (;;)
    {
      oldValue = Value();
      newValue = func(oldValue);

      if (CompareAndSet(oldValue, newValue))
      {
        break;
      }
    }

    return newValue;
  }

private:

  T mValue;

  ValidateFunc mValidator;

  std::mutex mReadMutex;
  std::mutex mWriteMutex;
};

} // namespace Concurrent
