#include "gtest/gtest.h"
#include "BigInt.h"
#include <string>

// base of positional notation
#define MODULE 1000000000

TEST(BigIntConstructor, InvalidStringFormat1) {
  try {
    BigInt a("qweasd");
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("Invalid format"), err.what());
  }
}

TEST(BigIntConstructor, InvalidStringFormat2) {
  try {
    BigInt a("1-123");
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("Invalid format"), err.what());
  }
}

TEST(BigIntConstructor, NegativeStringValue) {
  BigInt a("-1231241");
  EXPECT_EQ(a.isNegative(), true);
}

TEST(BigIntConstructor, BigStringValue) {
  BigInt a("123123123132123123211231");
  EXPECT_EQ(a, "123123123132123123211231");
}

TEST(BigIntConstructor, UnsignedIntValue) {
  BigInt a(ULONG_MAX);
  EXPECT_EQ(a, ULONG_MAX);
  // EXPECT_EQ(static_cast<std::string>(a), std::to_string(ULONG_MAX));
}

TEST(BigIntConstructor, UnsignedLongIntValue) {
  BigInt a(ULONG_MAX);
  EXPECT_EQ(static_cast<std::string>(a), std::string(std::to_string(ULONG_MAX)));
}

TEST(BigIntConstructor, NegativeIntValue) {
  BigInt a(-1);
  EXPECT_EQ(a.isNegative(), true);
}

TEST(BigIntConstructor, NonNegativeIntValue) {
  BigInt a(1);
  EXPECT_EQ(a.isNegative(), false);
}

TEST(BigIntConstructor, BigIntValue) {
  BigInt a(MODULE - 1);
  BigInt b(a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a.isNegative(), b.isNegative());
}

TEST(BigIntMethod, Size) {
  BigInt a;
  EXPECT_EQ(a.size(), sizeof(BigInt));
}

TEST(BigIntMethod, Length) {
  std::string num(std::to_string(MODULE - 1) + std::to_string(MODULE - 1) + std::to_string(MODULE - 1));
  BigInt a(num);
  EXPECT_EQ(a.length(), num.length() / std::to_string(MODULE - 1).length());
}

TEST(BigIntMethod, IsNegative) {
  BigInt a(1);
  EXPECT_EQ(a.isNegative(), false);
  BigInt b(0);
  EXPECT_EQ(b.isNegative(), false);
  BigInt c(-1);
  EXPECT_EQ(c.isNegative(), true);
}

TEST(BigIntOperator, AssignmentToInt) {
  BigInt a;
  a = MODULE;
  EXPECT_EQ(a, MODULE);
}

TEST(BigIntOperator, AssignmentToString) {
  BigInt a;
  a = std::to_string(MODULE);
  EXPECT_EQ(a, std::to_string(MODULE));
}

TEST(BigIntOperator, AssignmentToBigInt) {
  BigInt a;
  BigInt b(MODULE);
  a = b;
  EXPECT_EQ(a, b);
}

TEST(BigIntOperator, PreIncrement) {
  BigInt a(MODULE - 1);
  EXPECT_EQ(++a, MODULE);
}

TEST(BigIntOperator, PostIncrement) {
  BigInt a(MODULE - 1);
  EXPECT_EQ(a++, MODULE - 1);
  EXPECT_EQ(a, MODULE);
}

TEST(BigIntOperator, PreDecrement) {
  BigInt a(MODULE);
  EXPECT_EQ(--a, MODULE - 1);
}

TEST(BigIntOperator, PostDecrement) {
  BigInt a(MODULE);
  EXPECT_EQ(a--, MODULE);
  EXPECT_EQ(a, MODULE - 1);
}

TEST(BigIntOperator, SumOfBigInts) {
  BigInt a("123456789000000000");
  BigInt b("123456789");
  EXPECT_EQ(a + b, "123456789123456789");
  EXPECT_EQ(b + a, "123456789123456789");
  BigInt c(MODULE - 1);
  BigInt d(2);
  EXPECT_EQ(c + d, MODULE + 1);
  BigInt f(MODULE);
  BigInt g(-1 * MODULE);
  EXPECT_EQ(f + g, 0);
}

TEST(BigIntOperator, SubtractionOfBigInts) {
  BigInt a("123456789123456789");
  BigInt b("123456789");
  EXPECT_EQ(a - b, "123456789000000000");
  BigInt c(MODULE);
  BigInt d(2 * MODULE);
  EXPECT_EQ(c - d, -MODULE);
  BigInt f(MODULE);
  BigInt g(-MODULE);
  EXPECT_EQ(f - g, 2 * MODULE);
}

TEST(BigIntOperator, MultiplicationOfBigInts) {
  BigInt a(MODULE / 2);
  BigInt b(2);
  EXPECT_EQ(a * b, MODULE);
  EXPECT_EQ(b * a, MODULE);
  BigInt c(0);
  EXPECT_EQ(a * c, 0);
  BigInt d(-2);
  EXPECT_EQ(a * d, -MODULE);
  BigInt f(MODULE);
  BigInt g(MODULE);
  EXPECT_EQ(f * g, std::string(std::to_string(MODULE) + std::to_string(MODULE).erase(0, 1)));
}

TEST(BigIntOperator, DivisionOfBigInts) {
  BigInt a(MODULE);
  BigInt b(2);
  EXPECT_EQ(a / b, MODULE / 2);
  EXPECT_EQ(b / a, 0);
  BigInt c(0);
  try {
    a / c;
    FAIL() << "Expected 'division by zero' error";
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("division by zero"), err.what());
  }
  EXPECT_EQ(c / a, 0);
}

// TEST(BigIntOperator, RemainingOfBigInts) {
//   BigInt a(MODULE);
//   BigInt b(2);
//   EXPECT_EQ(a % b, 0);
//   BigInt c(2 * MODULE + 1);
//   EXPECT_EQ(a % c, a);
//   EXPECT_EQ(c % a, 1);
// }

TEST(BigIntOperator, EqualityOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a == b, true);
  EXPECT_EQ(a == c, false);
}

TEST(BigIntOperator, NonEqualityOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a != b, false);
  EXPECT_EQ(a != c, true);
}

TEST(BigIntOperator, LessOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a < b, false);
  EXPECT_EQ(a < c, false);
  EXPECT_EQ(c < a, true);
}

TEST(BigIntOperator, LessOrEqualOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a <= c, false);
  EXPECT_EQ(c <= a, true);
}

TEST(BigIntOperator, GreaterOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a > c, true);
  EXPECT_EQ(c > a, false);
}

TEST(BigIntOperator, GreaterOrEqualOfBigInts) {
  BigInt a(1);
  BigInt b(1);
  BigInt c(0);
  EXPECT_EQ(a >= b, true);
  EXPECT_EQ(a >= c, true);
  EXPECT_EQ(c >= a, false);
}

// TEST(BigIntOperator, ComparisonWithInt) {
//   BigInt a(LONG_MAX);
//   EXPECT_EQ(a < INT_MAX, false);
//   EXPECT_EQ(a > INT_MAX, true);
//   EXPECT_EQ(INT_MAX < a, true);
// }

// ADD COMPARISON WITH OTHER TYPES

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
