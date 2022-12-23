#pragma once

#include <iostream>

template<typename Ch, typename Tr, size_t I, typename... Ts>
struct tuplePrinter {
  static void print(std::basic_ostream<Ch, Tr>& os, std::tuple<Ts...> t) {
    tuplePrinter<Ch, Tr, I - 1, Ts...>::print(os, t);
    if (I < sizeof...(Ts))
      os << ", " << std::get<I>(t);
  }
};

template<typename Ch, typename Tr, typename... Ts>
struct tuplePrinter<Ch, Tr, 0, Ts...> {
  std::basic_ostream<Ch, Tr>& print(std::basic_ostream<Ch, Tr>& os, std::tuple<Ts...> t) {
    os << std::get<0>(t);
  }
};

template<typename Ch, typename Tr,typename... Ts>
struct tuplePrinter<Ch, Tr, -1, Ts...> {
  std::basic_ostream<Ch, Tr>& print(std::basic_ostream<Ch, Tr>& os, std::tuple<Ts...> t) {}
};


template<typename Ch, typename Tr, typename... Ts>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Ts...> t) {
  os << "("
  tuplePrinter<Ch, Tr, sizeof...(Ts), Ts>::print(os, t);
  return os << ")";
}
