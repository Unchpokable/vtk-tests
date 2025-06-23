cmake_minimum_required(VERSION 3.20)

project(vtk-composite-test)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectories
add_subdirectory(deps/vtk)
add_subdirectory(src)
