cmake_minimum_required(VERSION 3.10)
project(banjo_pc C)

set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c)

file (GLOB_RECURSE BANJO_SOURCES "banjo/*.c")

list(APPEND SOURCES ${BANJO_SOURCES})

add_executable(banjo ${SOURCES})

include_directories(
  platform/pc/include
  banjo/include
)