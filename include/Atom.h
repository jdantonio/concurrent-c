#pragma once

#include <mutex>
#include <functional>

template<typename T>
class Atom
{
public:

  typedef std::function<T(const T&)> UpdateFunc;
  typedef std::function<bool(const T&)> ValidateFunc;

  explicit Atom(const T& initialValue, ValidateFunc validator = [](const T&){ return true; })
    : mValue(initialValue)
    , mValidator(validator)
    {
    }

  virtual ~Atom() {  }

  T Value()
  {
    std::lock_guard<std::mutex> rlock(mReadMutex);
    return mValue;
  }

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
