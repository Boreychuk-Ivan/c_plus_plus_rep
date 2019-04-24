cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(coding_lib)

set(SOURCES coding_lib.cpp)
set(HEADERS coding_lib.h)

add_library(coding_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(coding_lib PUBLIC ${PROJECT_SOURCE_DIR})

target_include_directories(coding_lib PUBLIC ../src/matrix_lib)