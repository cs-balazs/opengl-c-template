cmake_minimum_required(VERSION 3.10)
project(gfx VERSION 1.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "./*.c")

add_library(${PROJECT_NAME} STATIC gfx.h ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} io glad image cglm)