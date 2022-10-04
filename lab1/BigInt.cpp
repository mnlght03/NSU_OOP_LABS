#include "BigInt.h"

BigInt::BigInt() {
  isNegative = 0;
  data.push_back(0);
}

BigInt::BigInt(int num) {
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
      isNegative = 1;
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

const BigInt BigInt::operator++(int) {
  BigInt temp = *this;
  ++*this;
  return temp;
}

BigInt& BigInt::operator--() {
  *this -= 1;
  return *this;
}

const BigInt BigInt::operator--(int) {
  BigInt temp = *this;
  --*this;
  return temp;
}

size_t BigInt::length() {
  return data.size();
}

BigInt operator+(const BigInt& a, const BigInt& b) {
  if (a.isNegative && !b.isNegative) {
    BigInt temp = a;
    temp.isNegative = 0;
    return b - temp;
  }
  else if (!a.isNegative && b.isNegative) {
    BigInt temp = b;
    temp.isNegative = 0;
    return a - b;
  }
  BigInt res;
  if (a.isNegative && b.isNegative) {
    res.isNegative = 1;
  }
  int carry = 0;
  for (int i = a.length() - 1, j = b.length() - 1; i >= 0 && j >= 0; --i, --j) {
    res.data.push_back((a.data[i] + b.data[j] + carry) % MODULE);
    carry = (a.data[i] + b.data[j] + carry) / MODULE;
  }
  a.length() > b.length() ?
    for (int i = a.length() - b.length() - 1; i >= 0; --i) {
      res.data.push_back((a.data[i] + carry) % MODULE);
      carry = (a.data[i] + carry) / MODULE;
    } :
    for (int j = b.length() - a.length() - 1; j >= 0; --j) {
      res.data.push_back((b.data[j] + carry) % MODULE);
      carry = (b.data[j] + carry) / MODULE
    }
  return res;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
  BigInt res;
  int carry = 0;
  for (int i = a.length() - 1, j = b.length() - 1; i >= 0 && j >= 0; --i, --j) {
    
  }
  a.length() > b.length() ?
    for (int i = a.length() - b.length() - 1; i >= 0; --i) {
      res.data.push_back((a.data[i] + carry) % MODULE);
      carry = (a.data[i] + carry) / MODULE;
    } :
    for (int j = b.length() - a.length() - 1; j >= 0; --j) {
      res.data.push_back((b.data[j] + carry) % MODULE);
      carry = (b.data[j] + carry) / MODULE
    }
}

BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


BigInt& BigInt::operator+=(const BigInt&) {

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
