#pragma once
#include "type_traits.h"

namespace mak {
using size_t = decltype(sizeof 0);

template <class T> constexpr remove_reference_t<T> &&move(T &&t) noexcept {
  return static_cast<remove_reference_t<T> &&>(t);
}

template <class T> T exchange(T &obj, T &&new_value) {
  T old = obj;
  obj = new_value;
  return old;
}

void swap(auto &lhs, auto &rhs) { lhs = exchange(rhs); }

template <class T, size_t N> swap(T (&a)[N], T (&b)[N]) {}
} // namespace mak