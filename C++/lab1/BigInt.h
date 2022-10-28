#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <vector>
#include <iomanip>  // stoi
#include <string>
#include <climits>  // INT_MAX
#include <algorithm>  // std::min


class Bigint {
  public:
    Bigint();
    Bigint(int);
    Bigint(long int); // works for unsigned int as well
    Bigint(unsigned long int);
    Bigint(std::string);  // throws std::invalid_argument on error
    Bigint(const Bigint&);
    ~Bigint();
    Bigint& operator=(const Bigint&);
    Bigint& operator=(const int&);
    Bigint& operator=(std::string);

    Bigint& operator++();
    const Bigint operator++(int);
    Bigint& operator--();
    const Bigint operator--(int);

    Bigint& operator+=(const Bigint&);
    Bigint& operator*=(const Bigint&);
    Bigint& operator-=(const Bigint&);
    Bigint& operator/=(const Bigint&);
    Bigint& operator%=(const Bigint&);

    friend Bigint operator+(const Bigint&, const Bigint&);
    friend Bigint operator-(const Bigint&, const Bigint&);
    friend Bigint operator*(const Bigint&, const Bigint&);
    friend Bigint operator/(const Bigint&, const Bigint&);
    friend Bigint operator%(const Bigint&, const Bigint&);
    // exponentiation
    // friend Bigint operator^(const Bigint&, int pow);

    // unary +
    Bigint operator+() const;
    // unary -
    Bigint operator-() const;

    bool operator==(const Bigint&) const;
    bool operator!=(const Bigint&) const;
    bool operator<(const Bigint&) const;
    bool operator>(const Bigint&) const;
    bool operator<=(const Bigint&) const;
    bool operator>=(const Bigint&) const;

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
    // sign of value
    bool isNegative() const;
    // length of stringified value
    size_t length() const;
    // size of vector
    size_t size() const;
    // size in bytes
    size_t sizeInBytes() const;
  private:
    std::vector<int> data;
    bool negative;
};


std::ostream& operator<<(std::ostream& o, const Bigint& i);

#endif  // BIGINT_H_
