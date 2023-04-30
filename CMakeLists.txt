cmake_minimum_required(VERSION 3.24)
project(pathfinding)

set(CMAKE_CXX_STANDARD 17)

add_executable(pathfinding main.cpp matrix.hpp maze.cpp maze.hpp pfalgorithm.cpp pfalgorithm.hpp bfs.cpp bfs.hpp event.hpp term.cpp term.hpp coord.cpp coord.hpp expected.hpp)
