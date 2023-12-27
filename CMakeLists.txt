cmake_minimum_required(VERSION 3.24)
project(pathfinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(pathfinding src/main.cpp src/matrix.hpp src/maze.cpp src/maze.hpp src/algorithms/pf_algorithm.cpp src/algorithms/pf_algorithm.hpp src/algorithms/bfs.cpp src/algorithms/bfs.hpp src/utility/event.hpp src/io/term.cpp src/io/term.hpp src/coord.cpp src/coord.hpp src/utility/expected.hpp src/io/printer.cpp src/io/printer.hpp src/algorithms/dfs.cpp src/algorithms/dfs.hpp src/options/opts.cpp src/options/opts.hpp src/utility/overload.hpp src/utility/utility.hpp src/runner.cpp src/runner.hpp src/options/concrete_options/opt_neighborhood_order.hpp src/options/concrete_options/opt_sleep_time.hpp src/observers/delayer.cpp src/observers/delayer.hpp src/utility/fwd.hpp src/utility/type_list.hpp
        src/utility/rgb.hpp
        src/algorithms/rands.cpp
        src/algorithms/rands.hpp
        src/options/concrete_options/opt_seed.hpp
        src/algorithms/astar.cpp
        src/algorithms/astar.hpp
        src/algorithms/greedy.cpp
        src/algorithms/greedy.hpp
        src/options/opt_util.hpp
        src/options/opt_util.cpp
        src/options/opts_impl.hpp
        src/options/concrete_options/opt_neighborhood_order.cpp
        src/options/concrete_options/opt_seed.cpp
        src/options/concrete_options/opt_sleep_time.cpp
        src/options/opts_concepts.hpp
        src/options/concrete_options/help.cpp
        src/options/concrete_options/help.hpp
        src/utility/zip_view.hpp
)
