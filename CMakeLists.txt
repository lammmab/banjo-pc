cmake_minimum_required(VERSION 3.10)
project(banjo_pc C CXX)

if(MSVC)
    add_compile_options(/w)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Od /Zi /DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi /DDEBUG")
else()
    add_compile_options(-Wall -Wextra -Wno-unused-parameter)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g -DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
endif()



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(SOURCES src/main.c)
file (GLOB_RECURSE BANJO_SOURCES "banjo/*.c")
list(APPEND SOURCES ${BANJO_SOURCES})

if(MSVC)
    add_definitions(-DENABLE_DX11)
endif()

add_compile_definitions(F3DEX_GBI)

add_executable(banjo ${SOURCES})

if(MSVC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_precompile_headers(banjo PRIVATE "include/libaudio_pch.h")
endif()

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