cmake_minimum_required(VERSION 3.12)
project(CPPAssignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ppm)

add_executable(CPPAssignment
        ppm/ppm.cpp
        ppm/ppm.h
        Color.h
        Image.cpp
        Image.h
        Vec3.h
        Array.h
        Array.cpp
        Filter.h
        Filter.cpp)
