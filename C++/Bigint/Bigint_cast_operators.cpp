#include "Bigint.h"
#include "Bigint_defines.h"

Bigint::operator int() const {
  if (this->size() > 2)
    throw std::overflow_error("integer overflow");
  size_t res = this->data[0];
  if (this->size() > 1)
    res += (size_t)this->data[1] * MODULE;
  if (!this->isNegative() && res > INT_MAX)
    throw std::overflow_error("integer overflow");
  if (this->isNegative() && res > (size_t)INT_MAX + 1) {
    throw std::overflow_error("integer overflow");
  }
  return this->isNegative() ? -res : res;
}

Bigint::operator unsigned int() const {
  if (this->size() > 2)
    throw std::overflow_error("unsigned integer overflow");
  size_t res = this->data[0];
  if (this->size() > 0)
    res += (size_t)this->data[1] * MODULE;
  if (res > UINT_MAX)
    throw std::overflow_error("unsigned integer overflow");
  return res;
}

Bigint::operator std::string() const {
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

std::ostream& operator<<(std::ostream& o, const Bigint& i) {
  return o << (std::string)i;
}
