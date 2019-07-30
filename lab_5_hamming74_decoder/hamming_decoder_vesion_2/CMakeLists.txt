cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(hamming_decoder)

set(SOURCES hamming_decoder.cpp hamming_decoder.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})