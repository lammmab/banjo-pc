cmake_minimum_required(VERSION 3.10)
project(banjo_pc C CXX)

## CMAKE VERSION ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

## COMPILER FLAGS ##
if(MSVC)
    set(USE_AUTO_VCPKG ON CACHE BOOL "Automatically use vcpkg on Windows")

    add_compile_options(/w)
else()
    add_compile_options(-Wall -Wextra -Wno-unused-parameter)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g -DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
endif()

add_compile_definitions(F3DEX_GBI)

## SDL2 ##

## GAME SOURCES ##
set(SOURCES src/main.c)
file(GLOB_RECURSE BANJO_SOURCES "banjo/*.c")
list(APPEND SOURCES ${BANJO_SOURCES})

## LIBULTRASHIP ##
add_subdirectory(libultraship)

## EXECUTABLE ##
add_executable(banjo ${SOURCES})

## LIBULTRASHIP ##
target_link_libraries(banjo PRIVATE libultraship)

## INCLUDES ##
target_include_directories(banjo PRIVATE 
    banjo/include
    libultraship/include
    include
)

## PCH ##
if(MSVC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_precompile_headers(banjo PRIVATE "include/libaudio_pch.h")
endif()
