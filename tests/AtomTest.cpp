#include <catch.hh>
#include <Atom.h>

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

TEST_CASE("Assignment", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType actual, expected;

  AtomType subject(0);

  expected = 100;

  subject = expected;
  REQUIRE( subject.Value() == expected );
}

TEST_CASE("== and !=", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;

  initial = 0;
  AtomType subject(initial);

  expected = subject.Value();
  REQUIRE( subject == expected );

  expected = subject.Value() + 100;
  REQUIRE( subject != expected );
}

TEST_CASE("Compare", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;

  initial = 0;
  AtomType subject(initial);

  expected = subject.Value();
  actual = subject.Compare(
      [expected](const ValueType& currentValue)
      { return expected == currentValue; });
  REQUIRE( actual );

  expected = subject.Value() + 100;
  actual = subject.Compare(
      [expected](const ValueType& currentValue)
      { return expected == currentValue; });
  REQUIRE( !actual );
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
      [incrementer](const ValueType& currentValue)
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
      [incrementer](const ValueType& currentValue)
      { return currentValue + incrementer; });
  REQUIRE( actual == expected );

  actual = subject.Value();
  REQUIRE( actual == expected );
}

TEST_CASE("With", "[Atom]")
{
  typedef std::pair<std::string, uint64_t> ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial;

  initial = ValueType("foo", 42);
  AtomType subject(initial);

  uint64_t actual{ 0 };
  uint64_t expected{ initial.second };

  subject.With(
          [&actual](const ValueType& currentValue)
          { actual = currentValue.second; });

  REQUIRE( actual == expected );
}

TEST_CASE("Modify", "[Atom]")
{
  typedef std::pair<std::string, uint64_t> ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual;

  initial = ValueType("foo", 0);
  AtomType subject(initial);

  uint64_t expected{ 42 };

  actual = subject.Modify(
          [expected](ValueType& currentValue)
          { currentValue.second = expected; });

  REQUIRE( subject.Value().second == expected );
  REQUIRE( actual.first == initial.first );
  REQUIRE( actual.second == expected );
}
