#specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(scheduler)
# Set the output folder where your program will be created
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
MESSAGE( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory("${PROJECT_SOURCE_DIR}/scheduler")

