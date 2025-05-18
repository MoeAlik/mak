#pragma once
#include "type_traits.h"

namespace mak {
template <class T> constexpr remove_reference_t<T> &&move(T &&t) noexcept {
  return static_cast<remove_reference_t<T> &&>(t);
}
void swap(auto &lhs, auto &rhs);
} // namespace mak