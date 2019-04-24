cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(test_calculator)

set(TSOURCES tests.cpp)

add_executable(test_calculator ${TSOURCES})

add_subdirectory(googletest)


target_link_libraries(test_calculator PUBLIC calculator_lib)
target_link_libraries(test_calculator PUBLIC gtest)

target_include_directories(calculator_lib PUBLIC ../src)
