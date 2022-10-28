#include "Bigint.h"
#include "Bigint_defines.h"

bool Bigint::isNegative() const {
  return negative;
}

bool Bigint::operator==(const Bigint& num) const {
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

bool Bigint::operator!=(const Bigint& num) const {
  return !(*this == num);
}

bool Bigint::operator<(const Bigint& num) const {
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

bool Bigint::operator>(const Bigint& num) const {
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

bool Bigint::operator<=(const Bigint& num) const {
  return !(*this > num);
}

bool Bigint::operator>=(const Bigint& num) const {
  return !(*this < num);
}

bool Bigint::operator==(const int& num) const {
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

bool Bigint::operator!=(const int& num) const {
  return !(*this == num);
}

bool Bigint::operator>(const int& num) const {
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

bool Bigint::operator<(const int& num) const {
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

bool Bigint::operator<=(const int& num) const {
  return !(*this > num);
}

bool Bigint::operator>=(const int& num) const {
  return !(*this < num);
}

bool Bigint::operator==(std::string str) const {
  Bigint temp(str);
  return *this == temp;
}

bool Bigint::operator!=(std::string str) const {
  Bigint temp(str);
  return *this != temp;
}

bool Bigint::operator<(std::string str) const {
  Bigint temp(str);
  return *this < temp;
}

bool Bigint::operator>(std::string str) const {
  Bigint temp(str);
  return *this > temp;
}

bool Bigint::operator<=(std::string str) const  {
  Bigint temp(str);
  return *this <= temp;
}

bool Bigint::operator>=(std::string str) const  {
  Bigint temp(str);
  return *this >= temp;
}
