cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(main)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})

target_link_libraries(main PUBLIC coding_lib)
# target_link_libraries(main PUBLIC matrix_lib)


target_include_directories(main PUBLIC ../src/coding_lib)
target_include_directories(main PUBLIC ../src/matrix_lib)
