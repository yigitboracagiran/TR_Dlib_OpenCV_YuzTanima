cmake_minimum_required(VERSION 3.26)

project(yuzTanima)

# Set C++17 as the standard for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# Find OpenCV and Dlib libraries
find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Add executable and link against OpenCV and Dlib
add_executable(yuzTanima faceRecognition.cpp)
target_link_libraries(yuzTanima ${OpenCV_LIBS})
target_link_libraries(yuzTanima dlib::dlib)
