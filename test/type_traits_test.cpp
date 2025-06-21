#include "headers/type_traits.h"

#include <stdexcept>
#include <type_traits>

#include "test/test.h"

namespace {
void test_remove_ref() {
    assert(std::is_same_v<mak::remove_reference_t<int>, int>, "regular case failed");
    assert(std::is_same_v<mak::remove_reference_t<int&>, int>, "l value ref case failed");
    assert(std::is_same_v<mak::remove_reference_t<int&&>, int>, "r value ref case failed");
}
}   // namespace

void test_type_traits() {
    test_remove_ref();
}