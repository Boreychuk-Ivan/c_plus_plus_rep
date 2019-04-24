cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(main)

set(SOURCES main.cpp)

add_executable(calculator ${SOURCES})

target_include_directories(calculator_lib PUBLIC ../src)
target_link_libraries(calculator PUBLIC calculator_lib)