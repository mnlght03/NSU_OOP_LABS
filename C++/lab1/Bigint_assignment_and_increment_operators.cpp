#include "Bigint.h"
#include "Bigint_defines.h"

Bigint& Bigint::operator=(const Bigint& num) {
  this->negative = num.negative;
  this->data = num.data;
  return *this;
}

Bigint& Bigint::operator=(const int& num) {
  this->negative = num < 0 ? 1 : 0;
  this->data.clear();
  this->data.push_back(num < 0 ? -num : num);
  return *this;
}

Bigint& Bigint::operator=(std::string str) {
  Bigint temp(str);
  *this = temp;
  return *this;
}

Bigint& Bigint::operator++() {  // ++i
  *this += 1;
  return *this;
}

const Bigint Bigint::operator++(int) {  // i++
  Bigint temp = *this;
  ++*this;
  return temp;
}

Bigint& Bigint::operator--() {  // --i
  *this -= 1;
  return *this;
}

const Bigint Bigint::operator--(int) {  // i--
  Bigint temp = *this;
  --*this;
  return temp;
}
