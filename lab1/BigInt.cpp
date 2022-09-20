#include "BigInt.h"


BigInt::BigInt(int num) {
  while (num) {
    data.push_back(num % MODULE);
    num /= MODULE;
  }
}

BigInt::BigInt(std::string) {}

BigInt::BigInt(const BigInt&){}
BigInt::~BigInt(){}

void BigInt::print() {
  for (int i = data.size(); i >= 0; i--)
    std::cout << data[i];
}

