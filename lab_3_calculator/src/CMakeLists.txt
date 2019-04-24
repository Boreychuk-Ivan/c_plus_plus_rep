cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(calculator_lib)

set(SOURCES calculator_lib.cpp)
set(HEADERS calculator_lib.h)

add_library(calculator_lib STATIC ${SOURCES} ${HEADERS})
