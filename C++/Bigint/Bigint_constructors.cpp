#include "Bigint.h"
#include "Bigint_defines.h"

Bigint::Bigint() {
  negative = false;
}

Bigint::Bigint(int num) {
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

Bigint::Bigint(long int num) {
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

Bigint::Bigint(unsigned long int num) {
  negative = false;
  if (!num)
    data.push_back(num);
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

Bigint::Bigint(const std::string &str) {
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

Bigint::Bigint(const Bigint& num) {
  data = num.data;
  negative = num.negative;
}

Bigint::~Bigint(){}
