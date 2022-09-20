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
         endPos = str.end() - str.begin();
  data.push_back(0);
  while (endPos) {
    int num = 0;
    len = (int)(endPos - len) >= 0 ? len : endPos;
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

void BigInt::print() {  // CHANGE ME!!!
  std::cout << data[data.size() - 1] << " ";
  for (int i = data.size() - 2; i >= 0; i--)
    std::cout << std::setfill('0') << std::setw(9) << data[i] << " ";
}

