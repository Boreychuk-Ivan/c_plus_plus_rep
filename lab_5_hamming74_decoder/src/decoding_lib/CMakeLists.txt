cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(decoding_lib)

set(SOURCES decoding_lib.cpp)
set(HEADERS decoding_lib.h)

add_library(decoding_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(decoding_lib PUBLIC ${PROJECT_SOURCE_DIR})

target_include_directories(decoding_lib PUBLIC ../src/matrix_lib)