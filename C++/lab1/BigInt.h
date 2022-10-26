#ifndef BIG_INT_H_
#define BIG_INT_H_

#include <iostream>
#include <vector>
#include <iomanip>  // stoi
#include <string>
#include <climits>  // INT_MAX
#include <algorithm>  // std::min


class BigInt {
  public:
    BigInt();
    BigInt(int);
    BigInt(long int); // works for unsigned int as well
    BigInt(unsigned long int);
    BigInt(std::string);  // throws std::invalid_argument on error
    BigInt(const BigInt&);
    ~BigInt();
    BigInt& operator=(const BigInt&);
    BigInt& operator=(const int&);
    BigInt& operator=(std::string);

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);
    // friend BigInt operator^(const BigInt&, const BigInt&);
    // friend BigInt operator&(const BigInt&, const BigInt&);
    // friend BigInt operator|(const BigInt&, const BigInt&);



    // BigInt operator+(const BigInt&, const int&);
    // BigInt operator-(const BigInt&, const int&);
    // BigInt operator*(const BigInt&, const int&);
    // BigInt operator/(const BigInt&, const int&);
    // BigInt operator%(const BigInt&, const int&);
    // friend BigInt operator^(const BigInt&, const BigInt&);
    // friend BigInt operator&(const BigInt&, const BigInt&);
    // friend BigInt operator|(const BigInt&, const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    bool operator==(const int&) const;
    bool operator!=(const int&) const;
    bool operator<(const int&) const;
    bool operator>(const int&) const;
    bool operator<=(const int&) const;
    bool operator>=(const int&) const;

    bool operator==(std::string) const;
    bool operator!=(std::string) const;
    bool operator<(std::string) const;
    bool operator>(std::string) const;
    bool operator<=(std::string) const;
    bool operator>=(std::string) const;

    operator int() const;
    operator unsigned int() const;
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
