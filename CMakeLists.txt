cmake_minimum_required(VERSION 4.0)

project(mak)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wpedantic
    -Werror
    -Wextra
)

add_executable(test main.cpp)
