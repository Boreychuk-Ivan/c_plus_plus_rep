cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CODING_LIB decoding_lib)
set(MATRIX_LIB matrix_lib)

add_subdirectory(${CODING_LIB})
add_subdirectory(${MATRIX_LIB})

