#include "utility.h"

namespace mak {
template <typename T> void swap(T &lhs, T &rhs) { T temp = std::move(lhs); }
} // namespace mak
