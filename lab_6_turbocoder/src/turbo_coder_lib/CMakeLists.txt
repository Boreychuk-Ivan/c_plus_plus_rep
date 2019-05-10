cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(turbo_coder_lib)

set(SOURCES turbo_coder_lib.cpp)
set(HEADERS turbo_coder_lib.h)

add_library(turbo_coder_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(turbo_coder_lib PUBLIC ${PROJECT_SOURCE_DIR})

target_include_directories(turbo_coder_lib PUBLIC ../src/matrix_lib)