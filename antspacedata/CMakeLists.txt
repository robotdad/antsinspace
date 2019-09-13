cmake_minimum_required (VERSION 3.8)

project ("antspacedata")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-w -g -pedantic -O3 -msse4.2 -march=native -DNDEBUG)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
add_executable (antspacedata "antspacedata.cpp")