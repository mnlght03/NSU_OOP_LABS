#ifndef BIG_INT_H_
#define BIG_INT_H_

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

class BigInt {
  public:
    BigInt();
    BigInt(int);
    BigInt(std::string);  // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();
    void print(); // for debugging
    BigInt& operator=(const BigInt&);  // возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator^(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);
    friend BigInt operator&(const BigInt&, const BigInt&);
    friend BigInt operator|(const BigInt&, const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;
    bool isNegative() const;
    size_t length() const;
    size_t size() const;  // size in bytes
  private:
    std::vector<int> data;
    bool negative;
};


std::ostream& operator<<(std::ostream& o, const BigInt& i);

#endif  // BIG_INT_H_
