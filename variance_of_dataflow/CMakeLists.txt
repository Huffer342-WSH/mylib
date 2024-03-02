cmake_minimum_required(VERSION 3.5)
project(variance_of_dataflow VERSION 0.1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/sources)

FILE(GLOB_RECURSE func_src sources/*.c)

add_library(variance_of_dataflow STATIC ${func_src})
add_executable(test test/test.c ${func_src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
