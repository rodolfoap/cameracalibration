cmake_minimum_required(VERSION 3.10)
project(calib)

# Force C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Equivalent to (CFLAGS) -g
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Binary calib will go to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Equivalent to (CFLAGS) -g
set(CMAKE_C_FLAGS "-g")

add_executable(calib calib.cpp)

# OPENCV ####################################
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(calib ${OpenCV_LIBS} stdc++fs)
