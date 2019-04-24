cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(test_hamm_coder74)

set(TSOURCES tests.cpp)

add_executable(test_hamm_coder74 ${TSOURCES})

add_subdirectory(googletest)


target_link_libraries(test_hamm_coder74 PUBLIC coding_lib)
target_link_libraries(test_hamm_coder74 PUBLIC gtest)

target_include_directories(coding_lib PUBLIC ../src)
