# Adapted from https://github.com/gamestabled/auto_nnsdk/blob/main/CMakeLists.txt

cmake_minimum_required(VERSION 3.5)

project(nnsdk-lite CXX ASM)

file(GLOB_RECURSE nnsdk_cxxsourcefiles ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_library(nnsdk ${nnsdk_cxxsourcefiles})

target_include_directories(nnsdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
