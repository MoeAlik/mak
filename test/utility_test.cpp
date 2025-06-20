#include "headers/utility.h"

#include <array>
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
    if (a != 2) {
        throw std::runtime_error("exchange failed to modify value of obj");
    }
    if (b != 1) {
        throw std::runtime_error("exchange failed to return original value of obj");
    }
}

void test_swaps() {
    int a = 1, b = 2;
    mak::swap(a, b);
    if (a != 2 or b != 1) {
        throw std::runtime_error("swap failed");
    }

    int lhs[17] = { 0 };
    int rhs[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    mak::swap(lhs, rhs);

    for (mak::size_t i {}; i < 17; ++i) {
        if (lhs[i] != 1 or rhs[i] != 0) {
            throw std::runtime_error("swapping array failed on item " + std::to_string(i));
        }
    }
}

//
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
    if (a != 1) {
        throw std::runtime_error("Forward failed to forward lvalue as lvalue");
    }

    a = forward_test(mak::move(lval));
    if (a != 0) {
        throw std::runtime_error("Forward failed to forward rvalue as rvalue");
    }
}

}   // namespace

void test_utility() {
    test_move();
    test_exchange();
    test_swaps();
    test_forward();
}
