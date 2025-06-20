#include "headers/utility.h"
#include "test/test.h"
#include <memory>
#include <stdexcept>

namespace {
struct Toy {
  Toy() = delete;
  Toy(const Toy &) = delete;
  Toy &operator=(const Toy &) = delete;
  Toy &operator=(Toy &&) noexcept { return *this; }
  Toy(int &&) noexcept {}
};

void test_move() {
  int dummy{};
  Toy toy(mak::move(dummy));
  toy = Toy(mak::move(1));

  int &dummy_ref = dummy;
  toy = Toy(mak::move(dummy_ref));
}

void test_exchange() {
  int a = 1;
  int b = mak::exchange(a, 2);
  if (a != 2) {
    throw std::runtime_error("exchange failed to modify value of obj");
  }
  if (b != 1) {
    throw std::runtime_error("exchange failed to return original value of obj");
  }
}

void test_swap() {
  auto a = std::make_unique<int>(1), b = std::make_unique<int>(2);
  mak::swap(a, b);
  if (*a != 2 or *b != 1) {
    throw std::runtime_error("swap failed");
  }
}
} // namespace

void test_utility() {
  test_move();
  test_exchange();
  test_swap();
}
