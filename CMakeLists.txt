cmake_minimum_required(VERSION 3.16)
project(HDmap)

set(CMAKE_CXX_STANDARD 14)

add_executable(HDmap main.cpp route.cpp route.h object.cpp object.h object_type.h route_type.h dijkstra.h dataLoad.h)