cmake_minimum_required(VERSION 3.3)
project(Triangles)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector3.cpp Vector3.h Line.cpp Line.h Plane.cpp Plane.h GeometryHelp.cpp GeometryHelp.h General.cpp General.h)
add_executable(Triangles ${SOURCE_FILES})