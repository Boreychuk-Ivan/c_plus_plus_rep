cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(encoder_fabric)

set(SOURCES src/turbo_coder_lib.cpp>
            src/hamming_encoder_lib.cpp>
            src/encoders_fabric.cpp)

set(HEADERS include/turbo_coder_lib.h>
            include/matrix_lib.h>
            include/hamming_encoder_lib.h>
            include/encoders_fabric.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
      PUBLIC ${PROJECT_SOURCE_DIR}/include)