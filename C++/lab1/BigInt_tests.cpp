#include "gtest/gtest.h"
#include "Bigint.h"
#include "Bigint_defines.h"
#include <string>

TEST(BigintConstructor, InvalidStringFormat1) {
  try {
    Bigint a("qweasd");
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("Invalid format"), err.what());
  }
}

TEST(BigintConstructor, InvalidStringFormat2) {
  try {
    Bigint a("1-123");
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("Invalid format"), err.what());
  }
}

TEST(BigintConstructor, NegativeStringValue) {
  Bigint a("-1231241");
  EXPECT_EQ(a.isNegative(), true);
}

TEST(BigintConstructor, BigStringValue) {
  Bigint a("123123123132123123211231");
  EXPECT_EQ(a, "123123123132123123211231");
}

TEST(BigintConstructor, UnsignedIntValue) {
  Bigint a(ULONG_MAX);
  EXPECT_EQ(a, ULONG_MAX);
  // EXPECT_EQ(static_cast<std::string>(a), std::to_string(ULONG_MAX));
}

TEST(BigintConstructor, UnsignedLongIntValue) {
  Bigint a(ULONG_MAX);
  EXPECT_EQ(static_cast<std::string>(a), std::string(std::to_string(ULONG_MAX)));
}

TEST(BigintConstructor, NegativeIntValue) {
  Bigint a(-1);
  EXPECT_EQ(a.isNegative(), true);
}

TEST(BigintConstructor, NonNegativeIntValue) {
  Bigint a(1);
  EXPECT_EQ(a.isNegative(), false);
}

TEST(BigintConstructor, BigintValue) {
  Bigint a(MODULE - 1);
  Bigint b(a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a.isNegative(), b.isNegative());
}

TEST(BigintMethod, SizeInBytes) {
  Bigint a;
  EXPECT_EQ(a.sizeInBytes(), sizeof(a));
}

TEST(BigintMethod, Size) {
  Bigint a(MODULE);
  EXPECT_EQ(a.size(), 2);
  a = MODULE - 1;
  EXPECT_EQ(a.size(), 1);
}

TEST(BigintMethod, Length) {
  std::string num(std::to_string(MODULE - 1) + std::to_string(MODULE - 1) + std::to_string(MODULE - 1));
  Bigint a(num);
  EXPECT_EQ(a.length(), 3 * SINGLE_DIGIT_LEN);
  Bigint b(MODULE);
  EXPECT_EQ(b.length(), SINGLE_DIGIT_LEN + 1);
}

TEST(BigintMethod, IsNegative) {
  Bigint a(1);
  EXPECT_EQ(a.isNegative(), false);
  Bigint b(0);
  EXPECT_EQ(b.isNegative(), false);
  Bigint c(-1);
  EXPECT_EQ(c.isNegative(), true);
}

TEST(BigintOperator, AssignmentToInt) {
  Bigint a;
  a = MODULE;
  EXPECT_EQ(a, MODULE);
}

TEST(BigintOperator, AssignmentToString) {
  Bigint a;
  a = std::to_string(MODULE);
  EXPECT_EQ(a, std::to_string(MODULE));
}

TEST(BigintOperator, AssignmentToBigint) {
  Bigint a;
  Bigint b(MODULE);
  a = b;
  EXPECT_EQ(a, b);
}

TEST(BigintOperator, PreIncrement) {
  Bigint a(MODULE - 1);
  EXPECT_EQ(++a, MODULE);
}

TEST(BigintOperator, PostIncrement) {
  Bigint a(MODULE - 1);
  EXPECT_EQ(a++, MODULE - 1);
  EXPECT_EQ(a, MODULE);
}

TEST(BigintOperator, PreDecrement) {
  Bigint a(MODULE);
  EXPECT_EQ(--a, MODULE - 1);
}

TEST(BigintOperator, PostDecrement) {
  Bigint a(MODULE);
  EXPECT_EQ(a--, MODULE);
  EXPECT_EQ(a, MODULE - 1);
}

TEST(BigintOperator, SumOfBigints) {
  Bigint a("123456789000000000");
  Bigint b("123456789");
  EXPECT_EQ(a + b, "123456789123456789");
  EXPECT_EQ(b + a, "123456789123456789");
  Bigint c(MODULE - 1);
  Bigint d(2);
  EXPECT_EQ(c + d, MODULE + 1);
  Bigint f(MODULE);
  Bigint g(-1 * MODULE);
  EXPECT_EQ(f + g, 0);
}

TEST(BigintOperator, SubtractionOfBigints) {
  Bigint a("123456789123456789");
  Bigint b("123456789");
  EXPECT_EQ(a - b, "123456789000000000");
  Bigint c(MODULE);
  Bigint d(2 * MODULE);
  EXPECT_EQ(c - d, -MODULE);
  Bigint f(MODULE);
  Bigint g(-MODULE);
  EXPECT_EQ(f - g, 2 * MODULE);
}

TEST(BigintOperator, MultiplicationOfBigints) {
  Bigint a(MODULE / 2);
  Bigint b(2);
  EXPECT_EQ(a * b, MODULE);
  EXPECT_EQ(b * a, MODULE);
  Bigint c(0);
  EXPECT_EQ(a * c, 0);
  Bigint d(-2);
  EXPECT_EQ(a * d, -MODULE);
  Bigint f(MODULE);
  Bigint g(MODULE);
  EXPECT_EQ(f * g, std::string(std::to_string(MODULE) + std::to_string(MODULE).erase(0, 1)));
}

TEST(BigintOperator, DivisionOfBigints) {
  Bigint a(MODULE);
  Bigint b(2);
  EXPECT_EQ(a / b, MODULE / 2);
  b = -2;
  EXPECT_EQ(a / b, -(MODULE / 2));
  EXPECT_EQ(b / a, 0);
  Bigint c(0);
  try {
    a / c;
    FAIL() << "Expected 'division by zero' error";
  } catch (std::invalid_argument const& err) {
    EXPECT_EQ(std::string("division by zero"), err.what());
  }
  EXPECT_EQ(c / a, 0);
  a = "59817259187298371928739182741928";
  b = "9894719213";
  EXPECT_EQ(a / b, Bigint("6045372071671173346386"));
  b = "989471921";
  EXPECT_EQ(a / b, Bigint("60453720735040819747263"));
}

TEST(BigintOperator, RemainingOfBigints) {
  Bigint a(MODULE);
  Bigint b(2);
  EXPECT_EQ(a % b, 0);
  Bigint c(2 * MODULE + 1);
  EXPECT_EQ(a % c, a);
  EXPECT_EQ(c % a, 1);
  EXPECT_EQ(c % b, 1);
  a = "59817259187298371928739182741928";
  b = "9894719213";
  EXPECT_EQ(a % b, Bigint("124427710"));
  b = "989471921";
  EXPECT_EQ(a % b, Bigint("127639705"));
}

TEST(BigintOperator, EqualityOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a == b, true);
  EXPECT_EQ(a == c, false);
}

TEST(BigintOperator, NonEqualityOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a != b, false);
  EXPECT_EQ(a != c, true);
}

TEST(BigintOperator, LessOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a < b, false);
  EXPECT_EQ(a < c, false);
  EXPECT_EQ(c < a, true);
}

TEST(BigintOperator, LessOrEqualOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a <= c, false);
  EXPECT_EQ(c <= a, true);
}

TEST(BigintOperator, GreaterOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a > c, true);
  EXPECT_EQ(c > a, false);
}

TEST(BigintOperator, GreaterOrEqualOfBigints) {
  Bigint a(1);
  Bigint b(1);
  Bigint c(0);
  EXPECT_EQ(a >= b, true);
  EXPECT_EQ(a >= c, true);
  EXPECT_EQ(c >= a, false);
}

// TEST(BigintOperator, ComparisonWithInt) {
//   Bigint a(LONG_MAX);
//   EXPECT_EQ(a < INT_MAX, false);
//   EXPECT_EQ(a > INT_MAX, true);
//   EXPECT_EQ(INT_MAX < a, true);
// }

// ADD COMPARISON WITH OTHER TYPES

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
