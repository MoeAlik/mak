#pragma once
#include "type_traits.h"

namespace mak {
using size_t = decltype(sizeof(const volatile unsigned long long int* const* const));
template <class T>
constexpr remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<mak::remove_reference_t<T>&&>(t);
}

template <class T, class U = T>
T exchange(T& obj, U&& new_value) noexcept {
    T old = mak::move(obj);
    obj = mak::move(new_value);
    return old;
}

template <class T>
void swap(T& lhs, T& rhs) noexcept {
    T old = mak::move(lhs);
    lhs = mak::move(rhs);
    rhs = mak::move(old);
}

template <class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept {
    for (size_t i {}; i < N; ++i) {
        mak::swap(a[i], b[i]);
    }
}

template <class T>
constexpr T&& forward(remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
constexpr T&& forward(remove_reference_t<T>&& t) noexcept {
    return static_cast<T&&>(t);
}

// template <class T1, class T2> struct pair {
//   T1 first;
//   T2 second;

//   constexpr pair() : first{}, second{} {}
//   constexpr pair(const T1 &x, const T2 &y) : first{x}, second{y} {}

//   template <class U1 = T1, class U2 = T2>
//   constexpr pair(U1 &&x, U2 &&y) : first{forward(x)}, second{forward(y)} {}
//   template <class U1, class U2>
//   constexpr pair(pair<U1, U2> &p) : first{p.first}, second{p.second} {}

//   template <class U1, class U2>
//   pair(const pair<U1, U2> &p) : first{p.first}, second{p.second} {}

//   template <class U1, class U2>
//   pair(pair<U1, U2> &&p) : first{forward(p.first)}, second{forward(p.second)}
//   {}

//   template <class U1, class U2>
//   constexpr pair(const pair<U1, U2> &&p)
//       : first{forward(p.first)}, second{forward(p.second)} {}

//   pair(const pair &p) = default;
//   pair(pair &&p) = default;

// pair &operator=(const pair& other);
// };

}   // namespace mak