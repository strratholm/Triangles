cmake_minimum_required(VERSION 3.3)
project(Triangles)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp VitalyZ_Vector3.cpp VitalyZ_Vector3.h VitalyZ_Line.cpp VitalyZ_Line.h VitalyZ_Plane.cpp VitalyZ_Plane.h VitalyZ_GeometryHelp.cpp VitalyZ_GeometryHelp.h VitalyZ_General.cpp VitalyZ_General.h)
add_executable(Triangles ${SOURCE_FILES})