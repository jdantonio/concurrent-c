#include "catch.hh"
#include "Atom.h"

TEST_CASE("Initialization", "[Atom]")
{
  typedef uint64_t ValueType;
  typedef Atom<ValueType> AtomType;

  ValueType initial, actual, expected;

  initial = 0;
  AtomType subject(initial);

  expected = initial;
  actual = subject.Value();
  REQUIRE(actual == expected);
}

//TEST("[Atom]", CompareAndSetWithoutValidationTest)
//{
    //typedef uint64_t ValueType;
    //typedef Atom<ValueType> AtomType;

    //ValueType initial, actual, expected;

    //initial = 0;
    //AtomType subject(initial);

    //expected = 100;
    //ASSERT_TRUE(subject.CompareAndSet(initial, expected));
    //actual = subject.Value();
    //ASSERT_EQ(actual, expected);

    //expected = subject.Value();
    //ASSERT_FALSE(subject.CompareAndSet(expected + 1, expected));
    //actual = subject.Value();
    //ASSERT_EQ(actual, expected);
//}

//TEST("[Atom]", ResetWithValueWithoutValidationTest)
//{
    //typedef uint64_t ValueType;
    //typedef Atom<ValueType> AtomType;

    //ValueType actual, expected;

    //AtomType subject(0);

    //expected = 100;

    //actual = subject.Reset(expected);
    //ASSERT_EQ(actual, expected);

    //actual = subject.Value();
    //ASSERT_EQ(actual, expected);
//}

//TEST("[Atom]", ResetWithLambdaWithoutValidationTest)
//{
    //typedef uint64_t ValueType;
    //typedef Atom<ValueType> AtomType;

    //ValueType initial, actual, expected;
    //ValueType incrementer = 200;

    //initial = 0;
    //AtomType subject(initial);

    //expected = initial + incrementer;

    //actual = subject.Reset(
            //[incrementer](ValueType currentValue)
            //{ return currentValue + incrementer; });
    //ASSERT_EQ(actual, expected);

    //actual = subject.Value();
    //ASSERT_EQ(actual, expected);
//}

//TEST("[Atom]", SwapWithoutValidationTest)
//{
    //typedef uint64_t ValueType;
    //typedef Atom<ValueType> AtomType;

    //ValueType initial, actual, expected;
    //ValueType incrementer = 200;

    //initial = 0;
    //AtomType subject(initial);

    //expected = initial + incrementer;

    //actual = subject.Swap(
            //[incrementer](ValueType currentValue)
            //{ return currentValue + incrementer; });
    //ASSERT_EQ(actual, expected);

    //actual = subject.Value();
    //ASSERT_EQ(actual, expected);
//}
