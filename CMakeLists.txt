cmake_minimum_required(VERSION 3.1)

include(CTest)

add_executable(tests tests.cpp)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED 11)
add_test(tests tests)
