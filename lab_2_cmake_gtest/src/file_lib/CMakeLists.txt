cmake_minimum_required(VERSION 2.8)

project(file_lib)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(SOURCES file_lib.cpp)
set(HEADERS file_lib.h)

add_library(file_lib STATIC ${SOURCES} ${HEADERS})
