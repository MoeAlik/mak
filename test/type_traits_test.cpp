#include "headers/type_traits.h"
#include "test/test.h"
#include <stdexcept>
#include <type_traits>

namespace {
void test_remove_ref() {
  if constexpr (!std::is_same_v<mak::remove_reference_t<int>, int>) {
    throw std::runtime_error("regular case failed");
  }
  if constexpr (!std::is_same_v<mak::remove_reference_t<int &>, int>) {
    throw std::runtime_error("l value ref case failed");
  }
  if constexpr (!std::is_same_v<mak::remove_reference_t<int &&>, int>) {
    throw std::runtime_error("r value ref case failed");
  }
}
} // namespace

void test_type_traits() { test_remove_ref(); }