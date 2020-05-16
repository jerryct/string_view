cmake_minimum_required(VERSION 3.10)

project(string_view)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third_party/googletest _build/googletest)

add_executable(unit_tests
  string_view_tests.cpp
  double_include.cpp
  string_view.h
)
target_link_libraries(unit_tests
  PRIVATE
    gtest_main
    -fsanitize=address,undefined,leak
)
target_compile_options(unit_tests
  PRIVATE
    -fsanitize=address,undefined,leak
    -Wall
    -Wextra
    -pedantic
    -Wconversion
    -Wsign-conversion
)
add_test(unit_tests unit_tests)
