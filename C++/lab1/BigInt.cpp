#include "BigInt.h"

// base of positional notation
static const int MODULE = 1000000000;

static const int SINGLE_DIGIT_LEN = 9;

BigInt::BigInt() {
  negative = false;
}

BigInt::BigInt(int num) {
  negative = false;
  if (num < 0) {
    negative = true;
    num = -num;
  }
  if (!num)
    data.push_back(num);
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

BigInt::BigInt(long int num) {
  negative = false;
  if (num < 0) {
    negative = true;
    num = -num;
  }
  if (!num)
    data.push_back(num);
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

BigInt::BigInt(unsigned long int num) {
  negative = false;
  if (!num)
    data.push_back(num);
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

BigInt::BigInt(std::string str) {
  negative = 0;
  size_t len = SINGLE_DIGIT_LEN,
         endPos = str.size();
  while (endPos) {
    int num = 0;
    len = (int)(endPos - len) > 0 ? len : endPos;
    std::string substr = str.substr(endPos - len, len);
    for (int i = 0; substr[i]; i++) {
      if (substr[0] == '-' && !(endPos - len))
        continue;
      if (substr[i] < '0' || substr[i] > '9')
        throw std::invalid_argument("Invalid format");
    }
    num = std::stoi(substr);
    if (num < 0 && (endPos - len) == 0) {
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

BigInt& BigInt::operator=(const BigInt& num) {
  this->negative = num.negative;
  this->data = num.data;
  return *this;
}

BigInt& BigInt::operator=(const int& num) {
  this->negative = num < 0 ? 1 : 0;
  this->data.clear();
  this->data.push_back(num < 0 ? -num : num);
  return *this;
}

BigInt& BigInt::operator=(std::string str) {
  BigInt temp(str);
  *this = temp;
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

size_t BigInt::sizeInBytes() const {
  return sizeof(*this);
}

size_t BigInt::size() const {
  return data.size();
}

size_t BigInt::length() const {
  return std::string(*this).length();
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
    return a - (-b);

  BigInt res;
  int carry = 0;
  for (int i = 0, j = 0; i < a.size() && j < b.size(); ++i, ++j) {
    res.data.push_back((a.data[i] + b.data[i] + carry) % MODULE);
    carry = (a.data[i] + b.data[i] + carry) / MODULE;
  }
  for (int i = b.size(); i < a.size(); ++i) {
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
  for (int i = 0, j = 0; i < a.size() && j < b.size(); ++i, ++j) {
    int temp = a.data[i] - carry;
    carry = temp < b.data[j] ? 1 : 0;
    res.data.push_back(temp + carry * MODULE - b.data[j]);
  }
  for (int i = b.size(); i < a.size(); ++i) {
    res.data.push_back(a.data[i] ? a.data[i] - carry : MODULE - 1 - carry); 
    carry = a.data[i] ? 0 : 1;
  }
  while (!res.data.back() && res.size() > 1)
    res.data.pop_back();
  return res;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
  if (a == 1)
    return b;
  if (a == -1)
    return -b;
  if (b == 1)
    return a;
  if (b == -1)
    return -a;
  BigInt res;
  if (b == 0) {
    res = 0;
    return res;
  }
  for (int i = 0; i < b.size(); ++i) {
    BigInt termOfMultiplication;
    for (int k = 0; k < i; ++k) // pad with zeros
      termOfMultiplication.data.push_back(0);
    for (int j = 0; j < a.size(); ++j) {
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
  if ((a.isNegative() && !b.isNegative()) ||
    (!a.isNegative() && b.isNegative()))
      res.negative = 1;
  return res;
}

namespace {
  int divideBySubtraction(BigInt a, BigInt b) {
    int res = 0;
    while (a > 0) {
      a -= b;
      res++;
    }
    return --res;
  }
  int getSubstrForDivision(std::string &sub, int &idx, const std::string dividend, const BigInt divisor) {
    int initalIdx = idx;
    while(BigInt(sub) < divisor && idx < dividend.length()) {
      sub += dividend[idx++];
    }
    return idx - initalIdx;
  }
} // namespace

BigInt operator/(const BigInt& a, const BigInt& b) {
  if (b == 0)
    throw std::invalid_argument("division by zero");
  if (b == 1)
    return a;
  if (b == -1)
    return -a;
  BigInt leftOp = a.isNegative() ? -a : a,
         rightOp = b.isNegative() ? -b : b,
         res(0);
  if (a == 0 || b.length() > a.length())
    return res;
  if ((a.isNegative() && !b.isNegative()) ||
      (!a.isNegative() && b.isNegative()))
        res.negative = 1;
  // if (a.size() == 1 && b.size() == 1) {
  //   res = (a.data[0] / b.data[0]);
  //   return res;
  // }
  // if (b.size() == 1) {
  //   for (int i = 0; i < a.length(); i++) {
  //     BigInt divOperand;
  //     for (int j = 0; j < i; j++) {
  //       divOperand.data.push_back(0);
  //     }
  //     if (!(a.data[i] / b.data[0]) && i)
  //       divOperand.data[divOperand.length() - 1] += a.data[i] * MODULE / b.data[0];
  //     else
  //       divOperand.data.push_back((a.data[i] / b.data[0]));
  //     res += divOperand;
  //     // std::cout << divOperand << std::endl;
  //   }
  //   return res;
  // }
  std::cout << "HERE" << std::endl;
  if (a.length() == b.length()) {
    BigInt num = a;
    while(num > 0) {
      num -= b;
      res++;
    }
    return --res;
  }
  std::string dividend(leftOp);
  std::string result;
  std::string sub = dividend.substr(0, rightOp.length());
  int idx = rightOp.length();
  
  getSubstrForDivision(sub, idx, dividend, rightOp);
  while (idx < dividend.length()) {
    std::cout << sub + " " + result<< std::endl;
    BigInt temp(sub);
    int quotient = divideBySubtraction(temp, rightOp);
    std::cout << "HERE" << std::endl;
    result += std::to_string(quotient);
    std::cout << "HERE" << std::endl;
    temp -= rightOp * BigInt(quotient);
    std::cout << "HERE" << std::endl;
    sub = (int)temp ? std::string(temp) : "";
    std::cout << "HERE" << std::endl;
    for (int i = 0; i < getSubstrForDivision(sub, idx, dividend, rightOp) - 1; i++)  // idx increments here
      result += "0";
  }
  res = BigInt(result);
  return --res;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
  BigInt leftOp = a.isNegative() ? -a : a,
         rightOp = b.isNegative() ? -b : b;
  while (!leftOp.isNegative()) {
    leftOp -= rightOp;
  }
  return leftOp + rightOp;
}

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

BigInt& BigInt::operator/=(const BigInt& num) {
  *this = *this / num;
  return *this;
}

BigInt& BigInt::operator%=(const BigInt& num) {
  *this = *this % num;
  return *this;
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
  if (this->isNegative() && !num.isNegative())
    return false;
  if (!this->isNegative() && num.isNegative())
    return false; 

  for (int i = 0; i < this->size(); ++i)
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

  for (int i = this->size() - 1; i >= 0; --i) {
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

  for (int i = this->size() - 1; i >= 0; --i) {
    int diff = this->data[i] - num.data[i];
    if (diff < 0)
      return false;
    if (diff > 0)
      return true;
  }

  return false;
}

bool BigInt::operator<=(const BigInt& num) const {
  return !(*this > num);
}

bool BigInt::operator>=(const BigInt& num) const {
  return !(*this < num);
}

bool BigInt::operator==(const int& num) const {
  if (this->size() > 2)
    return false;
  int temp = this->data[0];
  if (this->size() > 1) {
    if (!this->isNegative() && (size_t)this->data[1] * MODULE + temp > INT_MAX)
      return false;
    if (this->isNegative() && (size_t)this->data[1] * MODULE + temp > (size_t)INT_MAX + 1)
      return false;
    temp += this->data[1] * MODULE;
  }
  if (this->isNegative())
    temp = -temp;
  return temp == num;
}

bool BigInt::operator!=(const int& num) const {
  return !(*this == num);
}

bool BigInt::operator>(const int& num) const {
  if (this->size() > 2)
    return this->isNegative() ? false : true;
  int temp = this->data[0];
  if (this->size() > 1) {
    if (!this->isNegative() && (size_t)this->data[1] * MODULE + temp > INT_MAX)
      return true;
    if (this->isNegative() && (size_t)this->data[1] * MODULE + temp > (size_t)INT_MAX + 1)
      return false;
    temp += this->data[1] * MODULE;
  }
  if (this->isNegative())
    temp = -temp;
  return temp > num;
}

bool BigInt::operator<(const int& num) const {
  if (this->size() > 2)
    return this->isNegative() ? true : false;
  int temp = this->data[0];
  if (this->size() > 1) {
    if (!this->isNegative() && (size_t)this->data[1] * MODULE + temp > INT_MAX)
      return false;
    if (this->isNegative() && (size_t)this->data[1] * MODULE + temp > (size_t)INT_MAX + 1)
      return true;
    temp += this->data[1] * MODULE;
  }
  if (this->isNegative())
    temp = -temp;
  return temp < num;
}

bool BigInt::operator<=(const int& num) const {
  return !(*this > num);
}

bool BigInt::operator>=(const int& num) const {
  return !(*this < num);
}

bool BigInt::operator==(std::string str) const {
  BigInt temp(str);
  return *this == temp;
}

bool BigInt::operator!=(std::string str) const {
  BigInt temp(str);
  return *this != temp;
}

bool BigInt::operator<(std::string str) const {
  BigInt temp(str);
  return *this < temp;
}

bool BigInt::operator>(std::string str) const {
  BigInt temp(str);
  return *this > temp;
}

bool BigInt::operator<=(std::string str) const  {
  BigInt temp(str);
  return *this <= temp;
}

bool BigInt::operator>=(std::string str) const  {
  BigInt temp(str);
  return *this >= temp;
}

BigInt::operator int() const {
  if (this->size() > 2)
    throw std::overflow_error("integer overflow");
  size_t res = this->data[0];
  if (this->size() > 0)
    res += (size_t)this->data[1] * MODULE;
  if (!this->isNegative() && res > INT_MAX)
    throw std::overflow_error("integer overflow");
  if (this->isNegative() && res > (size_t)INT_MAX + 1) {
    throw std::overflow_error("integer overflow");
  }
  return this->isNegative() ? -res : res;
}

BigInt::operator unsigned int() const {
  if (this->size() > 2)
    throw std::overflow_error("unsigned integer overflow");
  size_t res = this->data[0];
  if (this->size() > 0)
    res += (size_t)this->data[1] * MODULE;
  if (res > UINT_MAX)
    throw std::overflow_error("unsigned integer overflow");
  return res;
}

BigInt::operator std::string() const {
  std::string str;
  if (this->isNegative())
    str += "-";
  str += std::to_string(this->data[this->size() - 1]);
  for (int i = this->size() - 2; i >= 0; --i) {
    std::string temp = std::to_string(this->data[i]);
    str += std::string(SINGLE_DIGIT_LEN - temp.length(), '0') + temp;
  }
  return str;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
  return o << (std::string)i;
}
