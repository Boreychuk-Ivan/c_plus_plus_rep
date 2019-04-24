cmake_minimum_required(VERSION 2.8)

project(main_project)
set(SOURCES tests.cpp)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

add_executable(main_project ${SOURCES})

target_link_libraries(main_project file_lib)
target_link_libraries(main_project sort_lib)
target_link_libraries(main_project gtest)

