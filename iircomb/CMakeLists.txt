cmake_minimum_required(VERSION 3.5)
project(fifo VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/sources)

FILE(GLOB_RECURSE func_src sources/*.c)

add_executable(iircomb test/test.c ${func_src})
add_executable(coef test/test_coef.c ${func_src})

target_compile_options(iircomb PRIVATE -std=c99 -O0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
