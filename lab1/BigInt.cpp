#include "BigInt.h"

static const int MODULE = 1000000000;
static const int SINGLE_DIGIT_LEN = 9;

// namespace {

// }


BigInt::BigInt() {
  negative = 0;
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
  this->negative = 0;
  size_t len = SINGLE_DIGIT_LEN,
         endPos = str.size();
  while (endPos) {
    int num = 0;
    len = (int)(endPos - len) > 0 ? len : endPos;
    num = stoi(str.substr(endPos - len, len));
    if (num < 0 && (endPos - len) == 0) {
      std::cout << "HERE " << std::endl;
      num *= -1;
      negative = 1;
    }
    data.push_back(num);
    endPos -= len;
    if (endPos == 1 && str[0] == '-') {
      negative = 1;
      break;
    }
  }
}

BigInt::BigInt(const BigInt& num) {
  data = num.data;
  negative = num.negative;
}

BigInt::~BigInt(){}

void BigInt::print() {
  if (this->isNegative())
    std::cout << "-";
  for (int i = data.size() - 1; i >= 0; i--)
    std::cout << std::setfill('0') << std::setw(9) << data[i] << " ";
  std::cout << std::endl;
}

BigInt& BigInt::operator=(const BigInt& num) {
  this->negative = num.negative;
  this->data = num.data;
  return *this;
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

size_t BigInt::size() const {
  return sizeof(BigInt);
}

size_t BigInt::length() const {
  return data.size();
}

bool BigInt::isNegative() const {
  return negative;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
  if (a.length() < b.length())
    return b + a;
  if (a.isNegative() && !b.isNegative())
    return b - (-a);
  if (!a.isNegative() && b.isNegative())
    return a - b;

  BigInt res;
  int carry = 0;
  for (int i = 0, j = 0; i < a.length() && j < b.length(); ++i, ++j) {
    res.data.push_back((a.data[i] + b.data[i] + carry) % MODULE);
    carry = (a.data[i] + b.data[i] + carry) / MODULE;
  }
  for (int i = b.length(); i < a.length(); ++i) {
    res.data.push_back((a.data[i] + carry) % MODULE);
    carry = (a.data[i] + carry) / MODULE;
  }
  if (carry)
    res.data.push_back(carry);
  return res;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
  if (a.isNegative() && !b.isNegative())
    return -((-a) + b);
  if (a.isNegative() && b.isNegative())
    return (-b) - (-a);
  if (!a.isNegative() && b.isNegative())
    return a + (-b);
  if (a < b)
    return -(b - a);

  BigInt res;
  int carry = 0;
  // perform operation when abs(a) >= abs(b)
  for (int i = 0, j = 0; i < a.length() && j < b.length(); ++i, ++j) {
    int temp = a.data[i] - carry;
    carry = temp < b.data[j] ? 1 : 0;
    res.data.push_back(temp + carry * MODULE - b.data[j]);
  }
  for (int i = b.length(); i < a.length(); ++i) {
    res.data.push_back(a.data[i] ? a.data[i] - carry : MODULE - 1 - carry); 
    carry = a.data[i] ? 0 : 1;
  }
  while (!res.data.back() && res.length() > 1)
    res.data.pop_back();
  return res;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
  BigInt res;
  res.negative = 1;
  if ((a.isNegative() && b.isNegative()) ||
      (!a.isNegative() && !b.isNegative()))
        res.negative = 0;
  for (int i = 0; i < b.length(); ++i) {
    BigInt termOfMultiplication;
    for (int k = 0; k < i; ++k) // pad with zeros
      termOfMultiplication.data.push_back(0);
    for (int j = 0; j < a.length(); ++j) {
      if (j)  // pad with zeros if a > MODULE
        termOfMultiplication.data.push_back(0);
      size_t temp = (size_t)b.data[i] * a.data[j];
      termOfMultiplication.data.push_back(temp % MODULE);
      if (temp / MODULE)
        termOfMultiplication.data.push_back(temp / MODULE);
      res += termOfMultiplication;
      termOfMultiplication.data.pop_back();
      if (temp / MODULE)
        termOfMultiplication.data.pop_back();
    }
  }
  return res;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
  // if (b == 0) // throw error
  // if (b == 1) // make int conversion
  //   return a;
  BigInt leftOp = a.isNegative() ? -a : a,
         rightOp = b. isNegative() ? -b : b,
         res(0);
  while (!leftOp.isNegative()) {
    leftOp -= rightOp;
    ++res;
  }
  return res;
}

BigInt operator%(const BigInt&, const BigInt&) {

}

BigInt operator^(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


BigInt& BigInt::operator+=(const BigInt& num) {
  *this = *this + num;
  return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
  *this = *this * num;
  return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
  *this = *this - num;
  return *this;
}

// BigInt& BigInt::operator/=(const BigInt& num) {
//   *this = *this / num;
//   return *this;
// }

// BigInt& BigInt::operator^=(const BigInt& num) {
//   *this = *this ^ num;
//   return *this;
// }

// BigInt& BigInt::operator%=(const BigInt& num) {
//   *this = *this % num;
//   return *this;
// }
// BigInt& BigInt::operator&=(const BigInt& num) {
//   *this = *this & num;
//   return *this;
// }

// BigInt& BigInt::operator|=(const BigInt& num) {
//   *this = *this | num;
//   return *this;
// }

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
  if (this->isNegative() && !num.isNegative())
    return false;
  if (!this->isNegative() && num.isNegative())
    return false; 

  for (int i = 0; i < this->length(); ++i)
    if (this->data[i] != num.data[i])
      return false;

  return true;
}

bool BigInt::operator!=(const BigInt& num) const {
  return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const {
  if (this->isNegative() && !num.isNegative())
    return true;
  if (this->isNegative() && num.isNegative()) {
    return -(*this) > -num;
  }
  if (this->length() < num.length())
    return true;
  if (num.length() < this->length())
    return false;

  for (int i = this->length() - 1; i >= 0; --i) {
    int diff = this->data[i] - num.data[i];
    if (diff < 0)
      return true;
    if (diff > 0)
      return false;
  }

  return false;
}

bool BigInt::operator>(const BigInt& num) const {
  if (!this->isNegative() && num.isNegative())
    return true;
  if (this->isNegative() && !num.isNegative())
    return false;
  if (this->isNegative() && num.isNegative())
    return -(*this) < -num;
  if (this->length() > num.length())
    return true;
  if (this->length() < num.length())
    return false;

  for (int i = this->length() - 1; i >= 0; --i) {
    int diff = this->data[i] - num.data[i];
    if (diff < 0)
      return false;
    if (diff > 0)
      return true;
  }

  return false;
}

bool BigInt::operator<=(const BigInt& num) const {
  if (this->isNegative() && !num.isNegative())
    return true;
  if (this->isNegative() && num.isNegative()) {
    return -(*this) > -num;
  }
  if (this->length() < num.length())
    return true;
  if (num.length() < this->length())
    return false;

  for (int i = this->length() - 1; i >= 0; --i) {
    int diff = this->data[i] - num.data[i];
    if (diff < 0)
      return true;
    if (diff > 0)
      return false;
  }

  return true;
}

bool BigInt::operator>=(const BigInt& num) const {
  if (!this->isNegative() && num.isNegative())
    return true;
  if (this->isNegative() && !num.isNegative())
    return false;
  if (this->isNegative() && num.isNegative())
    return -(*this) < -num;
  if (this->length() > num.length())
    return true;
  if (this->length() < num.length())
    return false;

  for (int i = this->length() - 1; i >= 0; --i) {
    int diff = this->data[i] - num.data[i];
    if (diff < 0)
      return false;
    if (diff > 0)
      return true;
  }

  return true;
}

// operator int() const;
// operator std::string() const;
