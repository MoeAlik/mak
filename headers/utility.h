#pragma once
#include "type_traits.h"
#include <type_traits>

namespace mak {
static inline constexpr const volatile unsigned long long int *const &entity{};
using size_t = decltype(sizeof(entity));
template <class T> constexpr remove_reference_t<T> &&move(T &&t) noexcept {
  return static_cast<mak::remove_reference_t<T> &&>(t);
}

template <class T, class U = T> T exchange(T &obj, U &&new_value) noexcept {
  T old = mak::move(obj);
  obj = mak::move(new_value);
  return old;
}

template <class T> void swap(T &lhs, T &rhs) noexcept {
  T old = mak::move(lhs);
  lhs = mak::move(rhs);
  rhs = mak::move(old);
}

template <class T, size_t N> void swap(T (&a)[N], T (&b)[N]) noexcept {
  for (size_t i{}; i < N; ++i) {
    mak::swap(a[i], b[i]);
  }
}

template <class T> constexpr T &&forward(remove_reference_t<T> &t) noexcept {
  return static_cast<T &&>(t);
}

template <class T> constexpr T &&forward(remove_reference_t<T> &&t) noexcept {
  return static_cast<T &&>(t);
}

template <class T1, class T2> struct pair {
  T1 first;
  T2 second;

  constexpr pair() : first{}, second{} {}
  constexpr pair(const T1 &x, const T2 &y) : first{x}, second{y} {}

  template <class U1 = T1, class U2 = T2>
  constexpr pair(U1 &&x, U2 &&y)
      : first{mak::forward<U1>(x)}, second{mak::forward<U2>(y)} {}

  template <class U1, class U2>
  pair(const pair<U1, U2> &p) : first{p.first}, second{p.second} {}

  template <class U1, class U2>
  constexpr pair(const pair<U1, U2> &&p)
      : first{mak::forward<U1>(p.first)}, second{mak::forward<U2>(p.second)} {}

  //  TODO: get, pair asssigment, <=>, ==
  void swap(pair<T1, T2> &other) noexcept { mak::swap(other, *this); }
};

template <size_t I, class T1, class T2> struct tuple_element<I, pair<T1, T2>> {
  static_assert(false, "Invalid index");
};

template <size_t I, class T1, class T2> struct tuple_element<0, pair<T1, T2>> {
  using type = T1;
};

template <size_t I, class T1, class T2> struct tuple_element<1, pair<T1, T2>> {
  using type = T2;
};

template <size_t I, typename T1, typename T2>
const tuple_element<I, pair<T1, T2>>::type &get(const pair<T1, T2> &p) {
  if constexpr (std::is_same_v < tuple_element<I, pair<T1, T2>>::type, T1) {
    return p.first;
  }
  return p.second;
}

template <size_t I, typename T1, typename T2>
const tuple_element<I, pair<T1, T2>>::type &&get(const pair<T1, T2> &&p) {
  if constexpr (std::is_same_v < tuple_element<I, pair<T1, T2>>::type, T1) {
    return p.first;
  }
  return p.second;
}

template <class T1, class T2>
constexpr mak::pair<T1, T2> make_pair(T1 &&x, T2 &&y) {
  return mak::pair<T1, T2>{mak::forward<T1>(x), mak::forward<T2>(y)};
}

} // namespace mak