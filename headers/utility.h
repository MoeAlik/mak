#pragma once
#include "type_traits.h"

namespace mak {

template <class T> constexpr remove_reference_t<T> &&move(T &&t) noexcept {
  return static_cast<remove_reference_t<T> &&>(t);
}

template <class T, class U = T> T exchange(T &obj, U &&new_value) noexcept {
  T old = obj;
  obj = new_value;
  return old;
}

void swap(auto &lhs, auto &rhs) noexcept { rhs = exchange(lhs, rhs); }

template <class T, size_t N> void swap(T (&a)[N], T (&b)[N]) noexcept {
  for (size_t i{}; i < N; ++i)
    swap(a[i], b[i]);
}

template <class T> constexpr T &&forward(remove_reference_t<T> &t) noexcept {
  return static_cast<T &&>(t);
}

template <class T> constexpr T &&forward(remove_reference_t<T> &&t) noexcept {
  // TODO: why do we need static_assert
  return static_cast<T &&>(t);
}

} // namespace mak