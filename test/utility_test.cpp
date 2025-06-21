#include "headers/utility.h"

#include <array>
#include <memory>
#include <stdexcept>
#include <string>

#include "test/test.h"

namespace {

struct move_only_t {
    move_only_t() = delete;
    move_only_t(const move_only_t&) = delete;
    move_only_t& operator=(const move_only_t&) = delete;
    move_only_t& operator=(move_only_t&&) noexcept { return *this; }
    move_only_t(int&&) noexcept {}
};

void test_move() {
    int dummy {};
    move_only_t move_only(mak::move(dummy));
    move_only = move_only_t(mak::move(1));

    int& dummy_ref = dummy;
    move_only = move_only_t(mak::move(dummy_ref));
}

void test_exchange() {
    int a = 1;
    int b = mak::exchange(a, 2);
    assert(a == 2, "exchange failed to modify value of obj");
    assert(b == 1, "exchange failed to return original value of obj");
}

void test_swaps() {
    int a = 1, b = 2;
    mak::swap(a, b);
    assert(a == 2 and b == 1, "swap failed");

    int lhs[17] = { 0 };
    int rhs[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    mak::swap(lhs, rhs);

    for (mak::size_t i {}; i < 17; ++i) {
        assert(lhs[i] == 1 and rhs[i] == 0, "swapping array failed on item");
    }
}

int forward_overload(int&) {
    return 1;
}

float forward_overload(int&&) {
    return 0;
}

template <typename T>
int forward_test(T&& val) {
    return forward_overload(mak::forward<T>(val));
}

void test_forward() {
    int lval {};
    int a = forward_test(lval);
    assert(a == 1, "Forward failed to forward lvalue as lvalue");

    a = forward_test(mak::move(lval));
    assert(a == 0, "Forward failed to forward rvalue as rvalue");
}

void test_pair_constructor() {
    mak::pair<long, double> default_init;
    assert(std::is_same_v<decltype(default_init.first), long>, "Default first is wrong type");
    assert(std::is_same_v<decltype(default_init.second), double>, "Default second is wrong type");
    assert(default_init.first == 0, "Default first has wrong value");
    assert(default_init.second == 0.0, "Default second has wrong value");

    mak::pair<long, double> value_init {};
    assert(value_init.first == 0, "Value first has wrong value");
    assert(value_init.second == 0.0, "Value second has wrong value");

    long first = 1;
    double second = 2.0;

    auto test_func = [&](auto pair) {
        assert(pair.first == 1, "const ref first has wrong value");
        assert(pair.second == 2.0, "const ref second has wrong value");
    };

    std::array<mak::pair<long, double>, 4> const_ref_pairs = {
        {{ 1, 2.0 }, { 1, second }, { first, 2.0 }, { first, second }}
    };

    for (const auto& p : const_ref_pairs) {
        test_func(p);
    }


}   // namespace

}   // namespace

void test_utility() {
    test_move();
    test_exchange();
    test_swaps();
    test_forward();
    test_pair_constructor();
}
