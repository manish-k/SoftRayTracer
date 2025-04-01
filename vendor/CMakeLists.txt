cmake_minimum_required (VERSION 3.8)

project(vendor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# stb
add_library(stb INTERFACE)
set(STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb)
target_sources(stb INTERFACE ${STB_DIR}/stb_image.h)
target_include_directories(stb INTERFACE ${STB_DIR})