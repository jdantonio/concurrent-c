#include <catch.hh>
#include <Atom.h>

namespace Concurrent
{

TEST_CASE("Initialization", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;

  initial = 0;
  AtomType subject(initial);

  expected = initial;
  actual = subject.Value();

  REQUIRE( actual == expected );
}

TEST_CASE("CompareAndSet (without validation)", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;

  initial = 0;
  AtomType subject(initial);

  expected = 100;
  REQUIRE( subject.CompareAndSet(initial, expected) );

  actual = subject.Value();
  REQUIRE( actual == expected);

  expected = subject.Value();
  REQUIRE(!subject.CompareAndSet(expected + 1, expected) );

  actual = subject.Value();
  REQUIRE( actual == expected );
}

TEST_CASE("Reset with value (without validation)", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType actual, expected;

  AtomType subject(0);

  expected = 100;

  actual = subject.Reset(expected);
  REQUIRE( actual == expected );

  actual = subject.Value();
  REQUIRE( actual == expected );
}

TEST_CASE("Reset with lambda (without validation)", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;
  ValueType incrementer = 200;

  initial = 0;
  AtomType subject(initial);

  expected = initial + incrementer;

  actual = subject.Reset(
      [incrementer](ValueType currentValue)
      { return currentValue + incrementer; });
  REQUIRE( actual == expected );

  actual = subject.Value();
  REQUIRE( actual == expected  );
}

TEST_CASE("Swap (without validation)", "[Atom]")
{

  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;
  ValueType initial, actual, expected;
  ValueType incrementer = 200;

  initial = 0;
  AtomType subject(initial);

  expected = initial + incrementer;

  actual = subject.Swap(
      [incrementer](ValueType currentValue)
      { return currentValue + incrementer; });
  REQUIRE( actual == expected );

  actual = subject.Value();
  REQUIRE( actual == expected );
}

} // namespace Concurrent
