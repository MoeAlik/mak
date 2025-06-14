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

# TODO: add glob thingy
set(SOURCES 
    main.cpp
    test/type_traits_test.cpp
    test/utility_test.cpp
)

add_executable(mak ${SOURCES})
target_include_directories(mak PRIVATE ${CMAKE_SOURCE_DIR})
