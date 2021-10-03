cmake_minimum_required(VERSION 3.10)

project(jerryct_string_view)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
option(JERRYCT_STRING_VIEW_ENABLE_TESTING "Enable unit tests." ON)

add_library(string_view INTERFACE)
add_library(jerryct::string_view ALIAS string_view)
target_include_directories(string_view INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:.>
)

if (JERRYCT_STRING_VIEW_ENABLE_TESTING)
  enable_testing()
  add_subdirectory(third_party/googletest _build/googletest)
  add_executable(unit_tests
    jerryct/string_view_tests.cpp
  )
  target_link_libraries(unit_tests
    PRIVATE
      jerryct::string_view
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
endif()
