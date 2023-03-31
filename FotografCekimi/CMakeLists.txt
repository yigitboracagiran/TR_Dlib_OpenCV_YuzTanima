cmake_minimum_required(VERSION 3.26)

project(fotografCekimi)

# Set C++17 as the standard for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV and Dlib libraries
find_package(OpenCV REQUIRED)

# Add include directories for OpenCV and Dlib
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable and link against OpenCV and Dlib
add_executable(fotografCekimi headshots.cpp)
target_link_libraries(fotografCekimi ${OpenCV_LIBS})