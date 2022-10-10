#include "BigInt.h"

static const int MODULE = 1000000000;
static const int SINGLE_DIGIT_LEN = 9;

BigInt::BigInt() {
  negative = 0;
  data.push_back(0);
}

BigInt::BigInt(int num) {
  negative = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
  }
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

BigInt::BigInt(std::string str) {
  size_t len = SINGLE_DIGIT_LEN,
         endPos = str.size();
  data.push_back(0);
  while (endPos) {
    int num = 0;
    len = (int)(endPos - len) > 0 ? len : endPos;
    num = stoi(str.substr(endPos - len, len));
    if (num < 0 && (endPos - len) == 0) {
      num *= -1;
      negative = 1;
    }
    if (*--data.end() < MODULE)
      num += *--data.end();
    *--data.end() = num % MODULE;
    data.push_back(num / MODULE);
    endPos -= len;
  }
}

BigInt::BigInt(const BigInt& num) {
  data = num.data;
  negative = num.negative;
}

BigInt::~BigInt(){}

void BigInt::print() {
  // std::cout << data[data.size() - 1] << " ";
  for (int i = data.size() - 1; i >= 0; i--)
    std::cout << std::setfill('0') << std::setw(9) << data[i] << " ";
  std::cout << std::endl << data.size() << std::endl;
}

BigInt& BigInt::operator++() {  // ++i
  *this += 1;
  return *this;
}

const BigInt BigInt::operator++(int) {  // i++
  BigInt temp = *this;
  ++*this;
  return temp;
}

BigInt& BigInt::operator--() {  // --i
  *this -= 1;
  return *this;
}

const BigInt BigInt::operator--(int) {  // i--
  BigInt temp = *this;
  --*this;
  return temp;
}

size_t BigInt::length() const {
  return data.size();
}

bool BigInt::isNegative() const {
  return negative;
}

BigInt operator+(const BigInt& a, const BigInt& b) {

}

BigInt operator-(const BigInt& a, const BigInt& b) {

}

BigInt operator*(const BigInt& a, const BigInt& b) {
  BigInt res;
  res.negative = 1;
  if ((a.isNegative() && b.isNegative()) ||
      (!a.isNegative() && !b.isNegative()))
        res.negative = 0;
  for (int i = (b.size() - 1) / sizeof(int); i >= 0; --i) {
    BigInt termOfMultiplication;
    for (int k = (b.size() - 1) / sizeof(int) + 1; k >= i; --k) // pad with zeros
      termOfMultiplication.data.push_back(0);
    for (int j = (a.size() - 1) / sizeof(int); j >= 0; --j) {
      size_t temp = b.data[i] * a.data[j];
      termOfMultiplication.data.back() += temp % MODULE;
      temp /= MODULE;
      temp += termOfMultiplication.data.back() / MODULE;
      termOfMultiplication.data.back() %= MODULE;
      termOfMultiplication.data.push_back(temp);
    }
    if (!termOfMultiplication.data.back())
      termOfMultiplication.data.pop_back();
    res += termOfMultiplication;
  }
  return res;
}

BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


BigInt& BigInt::operator+=(const BigInt& num) {

}

BigInt& BigInt::operator*=(const BigInt&) {

}

BigInt& BigInt::operator-=(const BigInt&) {

}

BigInt& BigInt::operator/=(const BigInt&) {

}

BigInt& BigInt::operator^=(const BigInt&) {

}

BigInt& BigInt::operator%=(const BigInt&) {

}
BigInt& BigInt::operator&=(const BigInt&) {

}

BigInt& BigInt::operator|=(const BigInt&) {

}

BigInt BigInt::operator+() const {
  return *this;
}  // unary +

BigInt BigInt::operator-() const {
  BigInt res = *this;
  res.negative ? res.negative = 0 : res.negative = 1;
  return res;
}  // unary -

bool BigInt::operator==(const BigInt& num) const {
  if (this->length() != num.length())
    return false;
  if ((this->isNegative() && num.isNegative()) ||
      (!this->isNegative() && !num.isNegative())) {
        for (int i = 0; i < this->length(); ++i)
          if (this->data[i] != num.data[i])
            return false;
  }
  return true;
}
bool BigInt::operator!=(const BigInt& num) const {
  return !(*this == num);
}

bool BigInt::operator<(const BigInt&) const {}
bool BigInt::operator>(const BigInt&) const {}
bool BigInt::operator<=(const BigInt&) const {}
bool BigInt::operator>=(const BigInt&) const {}

operator int() const;
operator std::string() const;
