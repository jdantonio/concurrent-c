// ChatTest
//------------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <rChat/include/Atom.h>

class AtomTest : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

TEST(ChatUtilsTest, InitializationTest)
{
    typedef uint64_t ValueType;
    typedef Atom<ValueType> AtomType;

    ValueType initial, actual, expected;

    initial = 0;
    AtomType subject(initial);

    expected = initial;
    actual = subject.Value();
    ASSERT_EQ(actual, expected);
}

TEST(ChatUtilsTest, CompareAndSetWithoutValidationTest)
{
    typedef uint64_t ValueType;
    typedef Atom<ValueType> AtomType;

    ValueType initial, actual, expected;

    initial = 0;
    AtomType subject(initial);

    expected = 100;
    ASSERT_TRUE(subject.CompareAndSet(initial, expected));
    actual = subject.Value();
    ASSERT_EQ(actual, expected);

    expected = subject.Value();
    ASSERT_FALSE(subject.CompareAndSet(expected + 1, expected));
    actual = subject.Value();
    ASSERT_EQ(actual, expected);
}

TEST(ChatUtilsTest, ResetWithValueWithoutValidationTest)
{
    typedef uint64_t ValueType;
    typedef Atom<ValueType> AtomType;

    ValueType actual, expected;

    AtomType subject(0);

    expected = 100;

    actual = subject.Reset(expected);
    ASSERT_EQ(actual, expected);

    actual = subject.Value();
    ASSERT_EQ(actual, expected);
}

TEST(ChatUtilsTest, ResetWithLambdaWithoutValidationTest)
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
    ASSERT_EQ(actual, expected);

    actual = subject.Value();
    ASSERT_EQ(actual, expected);
}

TEST(ChatUtilsTest, SwapWithoutValidationTest)
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
    ASSERT_EQ(actual, expected);

    actual = subject.Value();
    ASSERT_EQ(actual, expected);
}
