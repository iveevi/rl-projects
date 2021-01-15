# Set CMake version
cmake_minimum_required(VERSION 3.14)

# Compiler flags
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
        set(CMAKE_CXX_FLAGS "-g")
endif ()

# Main project
project(grid)

add_executable(grid main.cpp generate.cpp)

# Include directories
include_directories(PUBLIC ../zhetapi/engine)
