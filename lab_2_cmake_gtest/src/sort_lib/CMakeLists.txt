cmake_minimum_required(VERSION 2.8)
project(sort_lib)

set(SOURCES sort_lib.cpp)
set(HEADERS sort_lib.h)

add_library(sort_lib SHARED ${SOURCES} ${HEADERS})