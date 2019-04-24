cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

string(APPEND CMAKE_C_FLAGS_DEBUG " -DDEBUG_FLAG")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -DDEBUG_FLAG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(SRC_DIR src)
set(GTEST_DIR googletest)
set(PRJCT_DIR project)

add_subdirectory(${SRC_DIR})
add_subdirectory(${GTEST_DIR})
add_subdirectory(${PRJCT_DIR})
