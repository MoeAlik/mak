#pragma once
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

inline void test_suite(std::string_view func_name, std::function<void()> func,
                       std::ostringstream &oss, std::ostringstream &err) {

  static constexpr const char *bold_green = "\033[1;32m";
  static constexpr const char *bold_red = "\033[1;31m";
  static constexpr const char *reset = "\033[0m";

  oss << "Running Test \'" << func_name << "\': ";

  try {
    func();
    oss << bold_green << "PASS" << reset;
  } catch (std::runtime_error &e) {
    oss << bold_red << "FAIL" << reset;
    err << "Test \'" << func_name << "\': " << e.what() << '\n';
  }

  oss << '\n';
}

void test_type_traits();
void test_utility();

inline void run_test() {
  std::ostringstream oss{};
  std::ostringstream err{};

  test_suite("type_traits", test_type_traits, oss, err);
  test_suite("type_utility", test_utility, oss, err);

  auto err_str{err.view()};
  if (!err_str.empty()) {
    oss << '\n' << err_str << '\n';
  }

  std::cout << oss.str() << std::flush;
}
