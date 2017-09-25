#specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 17)

# Project's name

project(scheduler)
# Set the output folder where your program will be created
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
MESSAGE( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
MESSAGE( STATUS "CMAKE_GENERATOR: " ${CMAKE_GENERATOR} )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

if (APPLE)
    include_directories("${PROJECT_SOURCE_DIR}/platform/mac")
    include_directories("${PROJECT_SOURCE_DIR}/platform/mac/include")
    include_directories("${PROJECT_SOURCE_DIR}/platform/mac/client_lib")
    add_subdirectory("${PROJECT_SOURCE_DIR}/platform/mac")
endif()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


add_subdirectory("${PROJECT_SOURCE_DIR}/scheduler")

