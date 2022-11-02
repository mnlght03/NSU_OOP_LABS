#include "Bigint.h"
#include "Bigint_defines.h"

size_t Bigint::sizeInBytes() const {
  return sizeof(*this);
}

size_t Bigint::size() const {
  return data.size();
}

size_t Bigint::length() const {
  return std::string(*this).length();
}
