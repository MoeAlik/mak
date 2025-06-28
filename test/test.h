#pragma once
#include <exception>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace test {
inline void suite(std::string_view func_name, std::function<void()> func,
                  std::ostringstream &oss, std::ostringstream &err) {
  static constexpr const char *bold_green = "\033[1;32m";
  static constexpr const char *bold_red = "\033[1;31m";
  static constexpr const char *reset = "\033[0m";

  oss << "Running Test \'" << func_name << "\': ";

  try {
    func();
    oss << bold_green << "PASS" << reset;
  } catch (const std::exception &e) {
    oss << bold_red << "FAIL" << reset;
    err << "Test `" << func_name << "`: " << e.what() << '\n';
  }

  oss << '\n';
}

void type_traits();
void utility();

inline void run() {
  std::ostringstream oss{};
  std::ostringstream err{};

  suite("type_traits", type_traits, oss, err);
  suite("utility", utility, oss, err);

  auto err_str{err.view()};
  if (!err_str.empty()) {
    oss << '\n' << err_str;
  }

  std::cout << oss.str() << std::flush;
}

constexpr void assert(bool val, const std::string &msg) {
  if (!val) {
    throw std::runtime_error(msg);
  }
}

constexpr void assert_not(bool val, const std::string &msg) {
  assert(!val, msg);
}

} // namespace test