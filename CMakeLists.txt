cmake_minimum_required(VERSION 3.10)
project(banjo_pc C CXX)

if(MSVC)
    add_compile_options(/w)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c)

file (GLOB_RECURSE BANJO_SOURCES "banjo/*.c")

add_definitions(-DENABLE_DX11)

list(APPEND SOURCES ${BANJO_SOURCES})

add_executable(banjo ${SOURCES})

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/banjo/include/*")

set(INCLUDE_DIRS_FILTERED "")
foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${dir})
        list(APPEND INCLUDE_DIRS_FILTERED ${dir})
    endif()
endforeach()

include_directories(
  banjo/include
  ${INCLUDE_DIRS_FILTERED}
  libultraship/include
  libultraship/src
  include
)