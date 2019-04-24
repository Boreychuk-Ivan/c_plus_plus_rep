cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(matrix_lib)

set(SOURCES matrix_lib.cpp)
set(HEADERS matrix_lib.h)

add_library(matrix_lib INTERFACE)

target_sources(matrix_lib INTERFACE "${CMAKE_CURRENT_LIST_DIR}/matrix_lib.cpp")
target_sources(matrix_lib INTERFACE "${CMAKE_CURRENT_LIST_DIR}/matrix_lib.h")

target_include_directories(matrix_lib INTERFACE ${PROJECT_SOURCE_DIR})

add_custom_target(matrix_lib_ SOURCES ${CMAKE_CURRENT_LIST_DIR}/matrix_lib.h>
                                      ${CMAKE_CURRENT_LIST_DIR}/matrix_lib.cpp)
