cmake_minimum_required(VERSION 3.10)
project(io VERSION 1.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "./*.c")

add_library(${PROJECT_NAME} STATIC io.h ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})