cmake_minimum_required(VERSION 3.21)
project(netsim)

set(CMAKE_CXX_STANDARD 14)

add_executable(netsim main.cpp include/nodes.hpp src/nodes.cpp include/helpers.hpp)
