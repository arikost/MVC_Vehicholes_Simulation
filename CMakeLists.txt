cmake_minimum_required(VERSION 3.19)
project(MVC_Vehicholes_Simulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(MVC_Vehicholes_Simulation main.cpp Model.cpp Model.h Vehicle.h Warehouse.h View.cpp View.h Controller.h Geometry.h Geometry.cpp)