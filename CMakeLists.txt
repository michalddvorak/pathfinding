cmake_minimum_required(VERSION 3.24)
project(pathfinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(pathfinding src/main.cpp src/matrix.hpp src/maze.cpp src/maze.hpp src/algorithms/pf_algorithm.cpp src/algorithms/pf_algorithm.hpp src/algorithms/bfs.cpp src/algorithms/bfs.hpp src/utility/event.hpp src/io/term.cpp src/io/term.hpp src/coord.cpp src/coord.hpp src/utility/expected.hpp src/io/printer.cpp src/io/printer.hpp src/algorithms/dfs.cpp src/algorithms/dfs.hpp src/options/opts.cpp src/options/opts.hpp src/utility/overload.hpp src/utility/utility.hpp src/runner.cpp src/runner.hpp src/options/opt_neighborhood_order.hpp src/options/opt_sleep_time.hpp)
