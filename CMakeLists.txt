cmake_minimum_required(VERSION 3.1)
project(intmem)

include(CTest)

add_executable(tests_cxx11 tests.cpp)
set_property(TARGET tests_cxx11 PROPERTY CXX_STANDARD 11)
set_property(TARGET tests_cxx11 PROPERTY CXX_STANDARD_REQUIRED)
add_test(tests_cxx11 tests_cxx11)

add_executable(tests_cxx20 tests.cpp)
set_property(TARGET tests_cxx20 PROPERTY CXX_STANDARD 20)
set_property(TARGET tests_cxx20 PROPERTY CXX_STANDARD_REQUIRED)
add_test(tests_cxx20 tests_cxx20)
