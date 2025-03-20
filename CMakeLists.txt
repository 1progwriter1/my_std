cmake_minimum_required(VERSION 3.28.1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET run)

project(MY_STD)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${TARGET} ${SOURCES})

include_directories(headers)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(../MyLibraries/headers/)

add_compile_options(-fcolor-diagnostics)
