cmake_minimum_required(VERSION 3.24)
project(pathfinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(pathfinding src/main.cpp src/matrix.hpp src/maze.cpp src/maze.hpp src/algorithms/pfalgorithm.cpp src/algorithms/pfalgorithm.hpp src/algorithms/bfs.cpp src/algorithms/bfs.hpp src/utility/event.hpp src/io/term.cpp src/io/term.hpp src/coord.cpp src/coord.hpp src/utility/expected.hpp src/io/printer.cpp src/io/printer.hpp src/algorithms/dfs.cpp src/algorithms/dfs.hpp)
