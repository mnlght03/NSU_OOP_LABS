#pragma once

#include <iostream>
#include <type_traits>
#include <tuple>

template<typename T>
void formatOutput(std::ostream& os, const T& elem) {
  if constexpr (std::is_same_v<std::remove_reference_t<T>, bool>) {
    os << (elem ? "true" : "false");
  } else if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string>) {
    os << "\"" << elem << "\"";
  } else if constexpr (std::is_same_v<std::remove_reference_t<T>, char> ||
            std::is_same_v<std::remove_reference_t<T>, unsigned char>) {
    os << "\'" << elem << "\'";
  } else {
    os << elem;
  }
}

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& t) {
  os << "(";
  size_t n = 0;
  std::apply([&](const Ts&... args) { 
    ((formatOutput(os, args), os << (++n < sizeof...(Ts) ? ", " : "")), ...);
  }, t);
  return os << ")";
}
