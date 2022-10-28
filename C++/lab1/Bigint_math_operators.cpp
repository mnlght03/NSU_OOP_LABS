#include "Bigint.h"
#include "Bigint_defines.h"

namespace {
  int signOfMultDivResult(Bigint a, Bigint b) {
    if ((a.isNegative() && !b.isNegative()) ||
        (!a.isNegative() && b.isNegative()))
          return -1;
    return 1;
  }
  int divideBySubtraction(Bigint a, Bigint b) {
    int res = 0;
    while (a >= b) {
      a -= b;
      res++;
    }
    return res;
  }
  int getSubstrForDivision(std::string &sub, int &idx, const std::string dividend, const Bigint divisor) {
    if (idx == dividend.length()) {
      idx++;
      return 0;
    }
    int initalIdx = idx;
    int temp = 0;
    if (sub.empty() && idx < dividend.length())
      sub += dividend[idx++];
    while(idx < dividend.length() && Bigint(sub) < divisor) {
      sub += dividend[idx++];
    }
    return idx - initalIdx;
  }
} // namespace

Bigint operator+(const Bigint& a, const Bigint& b) {
  if (a.length() < b.length())
    return b + a;
  if (a.isNegative() && !b.isNegative())
    return b - (-a);
  if (!a.isNegative() && b.isNegative())
    return a - (-b);

  Bigint res;
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
}  // operator+

Bigint operator-(const Bigint& a, const Bigint& b) {
  if (a.isNegative() && !b.isNegative())
    return -((-a) + b);
  if (a.isNegative() && b.isNegative())
    return (-b) - (-a);
  if (!a.isNegative() && b.isNegative())
    return a + (-b);
  if (a < b)
    return -(b - a);

  Bigint res;
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
}  // operator-

Bigint operator*(const Bigint& a, const Bigint& b) {
  if (a == 1)
    return b;
  if (a == -1)
    return -b;
  if (b == 1)
    return a;
  if (b == -1)
    return -a;

  Bigint res(0);

  if (a == 0 || b == 0)
    return res;

  for (int i = 0; i < b.size(); ++i) {
    Bigint termOfMultiplication;
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
  if (signOfMultDivResult(a, b) < 0)
      res.negative = 1;
  return res;
}  // operator*

Bigint operator/(const Bigint& a, const Bigint& b) {
  if (b == 0)
    throw std::invalid_argument("division by zero");
  if (b == 1)
    return a;
  if (b == -1)
    return -a;
  Bigint leftOp = a.isNegative() ? -a : a,
         rightOp = b.isNegative() ? -b : b,
         res(0);
  if (a == 0 || b.length() > a.length())
    return res;
  if (a.length() == b.length()) {
    res.data =  Bigint(divideBySubtraction(leftOp, rightOp)).data;  // store the result and keep the sign
    return res;
  }
  if (a.size() == 1 && b.size() == 1) {
    res = (a.data[0] / b.data[0]);
  } else {
    std::string dividend(leftOp);
    std::string result = "";
    std::string sub = dividend.substr(0, rightOp.length());
    int idx = rightOp.length();
    getSubstrForDivision(sub, idx, dividend, rightOp);
    while (idx <= dividend.length()) {
      Bigint temp(sub);
      int quotient = divideBySubtraction(temp, rightOp);
      result += std::to_string(quotient);
      temp -= rightOp * Bigint(quotient);
      sub = temp == 0 ? "" : std::string(temp);
      // idx increments here
      int offset = getSubstrForDivision(sub, idx, dividend, rightOp) - 1;
      for (int i = 0; i < offset; i++)
        result += "0";
    }
    res = Bigint(result);
  }
  if (signOfMultDivResult(a, b) < 0)
      res.negative = 1;
  return res;
}  // operator/

Bigint operator%(const Bigint& a, const Bigint& b) {
  return a - b * (a / b);
}

Bigint& Bigint::operator+=(const Bigint& num) {
  *this = *this + num;
  return *this;
}

Bigint& Bigint::operator*=(const Bigint& num) {
  *this = *this * num;
  return *this;
}

Bigint& Bigint::operator-=(const Bigint& num) {
  *this = *this - num;
  return *this;
}

Bigint& Bigint::operator/=(const Bigint& num) {
  *this = *this / num;
  return *this;
}

Bigint& Bigint::operator%=(const Bigint& num) {
  *this = *this % num;
  return *this;
}

Bigint Bigint::operator+() const {
  return *this;
}  

Bigint Bigint::operator-() const {
  Bigint res = *this;
  res.negative ? res.negative = 0 : res.negative = 1;
  return res;
}