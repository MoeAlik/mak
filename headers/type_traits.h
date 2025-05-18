#pragma once

namespace mak {
template <class T> struct remove_reference {
  using type = T;
};
template <class T> struct remove_reference<T &> {
  using type = T;
};
template <class T> struct remove_reference<T &&> {
  using type = T;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;
} // namespace mak
