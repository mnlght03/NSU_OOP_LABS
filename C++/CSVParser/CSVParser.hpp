#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <fstream>
#include <sstream>

namespace {
  template<typename T>
  T formatRecord(const std::string& record) {
    return T(record);
  }

  template<>
  int formatRecord(const std::string& record) {
    size_t pos;
    int res = std::stoi(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  long formatRecord(const std::string& record) {
    size_t pos;
    long res = std::stol(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  float formatRecord(const std::string& record) {
    size_t pos;
    float res = std::stof(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  double formatRecord(const std::string& record) {
    size_t pos;
    double res = std::stod(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  unsigned int formatRecord(const std::string& record) {
    size_t pos;
    unsigned int res = std::stoul(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  unsigned long formatRecord(const std::string& record) {
    size_t pos;
    unsigned long res = std::stoul(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  unsigned long long formatRecord(const std::string& record) {
    size_t pos;
    unsigned long long res = std::stoull(record, &pos);
    if (pos != record.length())
      throw std::invalid_argument("Invalid record type");
    return res;
  }

  template<>
  bool formatRecord(const std::string& record) {
    if (record.compare("true"))
      return true;
    if (record.compare("false"))
      return false;
    throw std::invalid_argument("Invalid record type");
  }

template<typename... Ts>
class iter {
  std::ifstream *fileptr;
  std::string str;
  std::tuple<Ts...> recordTuple;
  size_t _startLine = 0;
  size_t row = 0, col = 0;
  char delimeter = ',';
  void skipLines(const size_t& N) {
    if (!fileptr)
      return;
    for (size_t i = 0; i < N; i++) {
      if (!std::getline(*fileptr, str)) {
        fileptr = nullptr;
        break;
      }
      ++row;
    }
  }
  template<typename T>
  void readRecord(std::stringstream& ss, T& elem) {
    std::string record;
    if (!std::getline(ss, record, delimeter)) {
      std::cerr << "Error reading records at line " + std::to_string(row) << std::endl;
      return;
    }
    ++col;
    try {
      elem = formatRecord<std::remove_reference_t<T>>(record);
    } catch (const std::invalid_argument& err) {
      std::cerr << "Invalid record at (line, col): ("
                   + std::to_string(row) + ", " + std::to_string(col)
                   + "): \'" + record + "\'. " << std::endl;
    }
  }
  public:
    iter(std::ifstream *file, size_t startLine) : fileptr(file), _startLine(startLine) {
      skipLines(startLine);
    }
    iter(std::ifstream *file, size_t startLine, char delim) : fileptr(file), _startLine(startLine), delimeter(delim) {
      skipLines(startLine);
    }
    virtual ~iter() = default;
    iter<Ts...>& operator++() {
      if (this->fileptr == nullptr)
        return *this;
      if (!std::getline(*fileptr, str)) {
        fileptr = nullptr;
        return *this;
      }
      // for CRLF line breaks
      if (!str.empty() && str[str.length() - 1] == '\r')
        str.erase(str.length() - 1);
      col = 0;
      std::stringstream s(str);
      std::apply([&](Ts&... args) { (readRecord(s, args), ...); }, recordTuple);
      ++row;
      return *this;
    }
    iter<Ts...> operator++(int) {
      iter<Ts...> ret = *this;
      ++*this;
      return ret;
    }
    std::tuple<Ts...>& operator*() {
      return recordTuple;
    }
    iter<Ts...>& begin() {
      return ++*this;
    }
    iter<Ts...> end() const {
      return iter(nullptr, 0);
    }
    bool operator==(const iter& it) const {
      return this->fileptr == it.fileptr;
    }
    bool operator!=(const iter& it) const {
      return !(*this == it);
    }
};

}  // namespace

template<typename... Ts>
class CSVParser : public iter<Ts...> {
  public:
    using iter<Ts...>::iter;    
};
