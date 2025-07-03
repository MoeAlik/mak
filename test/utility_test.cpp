#include "headers/utility.h"

#include <array>
#include <memory>
#include <stdexcept>
#include <string>

#include "test/test.h"

using test::assert;
using test::assert_not;

namespace {

struct move_only_t {
  move_only_t() = delete;
  move_only_t(const move_only_t &) = delete;
  move_only_t &operator=(const move_only_t &) = delete;
  move_only_t &operator=(move_only_t &&) noexcept { return *this; }
  move_only_t(int &&) noexcept {}
};

void move() {
  int dummy{};
  move_only_t move_only(mak::move(dummy));
  move_only = move_only_t(mak::move(1));

  int &dummy_ref = dummy;
  move_only = move_only_t(mak::move(dummy_ref));
}

void exchange() {
  int a = 1;
  int b = mak::exchange(a, 2);
  assert(a == 2, "exchange failed to modify value of obj");
  assert(b == 1, "exchange failed to return original value of obj");
}

void swaps() {
  int a = 1, b = 2;
  mak::swap(a, b);
  assert(a == 2 and b == 1, "swap failed");

  int lhs[17] = {0};
  int rhs[17] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  mak::swap(lhs, rhs);

  for (mak::size_t i{}; i < 17; ++i) {
    assert(lhs[i] == 1 and rhs[i] == 0, "swapping array failed on item");
  }
}

int forward_overload(int &) { return 1; }

float forward_overload(int &&) { return 0; }

template <typename T> int forward_test(T &&val) {
  return forward_overload(mak::forward<T>(val));
}

void forward() {
  int lval{};
  int a = forward_test(lval);
  assert(a == 1, "Forward failed to forward lvalue as lvalue");

  a = forward_test(mak::move(lval));
  assert(a == 0, "Forward failed to forward rvalue as rvalue");
}

void pair_constructor() {
  mak::pair<long, double> default_init;
  assert(std::is_same_v<decltype(default_init.first), long>,
         "Default first is wrong type");
  assert(std::is_same_v<decltype(default_init.second), double>,
         "Default second is wrong type");
  assert(default_init.first == 0, "Default first has wrong value");
  assert(default_init.second == 0.0, "Default second has wrong value");

  mak::pair<long, double> value_init{};
  assert(value_init.first == 0, "Value first has wrong value");
  assert(value_init.second == 0.0, "Value second has wrong value");

  long first = 1;
  double second = 2.0;

  auto func = [&](auto pair) {
    assert(pair.first == 1, "const ref first has wrong value");
    assert(pair.second == 2.0, "const ref second has wrong value");
  };

  std::array<mak::pair<long, double>, 4> const_ref_pairs = {
      {{1, 2.0}, {1, second}, {first, 2.0}, {first, second}}};

  for (const auto &p : const_ref_pairs) {
    func(p);
  }

  [[maybe_unused]] auto const_ref_pair_input{mak::make_pair(1, 1ll)};

  [[maybe_unused]] auto forwarding_l_value_pair(const_ref_pair_input);
}

void pair_swap() {
  auto p1 = mak::make_pair(5.f, 7ull);
  auto p2 = mak::make_pair(3.f, 2ull);

  p1.swap(p2);

  assert(p1.first == 3.f, "first first wrong");
  assert(p1.second == 2ull, "first second wrong");
  assert(p2.first == 5.f, "second first wrong");
  assert(p2.second == 7ull, "second second wrong");
}

void pair_get() {
  auto p1 = mak::make_pair(5.f, 7ull);
  auto first = mak::get<0>(p1);
  auto second = mak::get<1>(p1);
  assert(std::is_same_v<decltype(first), float>, "get 0 wrong");
  assert(std::is_same_v<decltype(second), size_t>, "get 1 wrong");

  // first = mak::get<float>(p1);
  // second = mak::get<size_t>(p1);
}

} // namespace

void test::utility() {
  move();
  exchange();
  swaps();
  forward();
  pair_constructor();
  pair_swap();
  pair_get();
}
