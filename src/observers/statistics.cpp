#include "statistics.hpp"

statistics::statistics(pf_algorithm* algorithm)
{
    algorithm->register_closed(closed_callback());
    algorithm->register_open(open_callback());
    algorithm->register_path(path_callback());
}

void statistics::print_statistics()
{
    std::cout << fmt("Path length: %u\n"
                     "Number of visited nodes: %u\n"
                     "Number of closed nodes: %u\n"
                     "Number of opened nodes: %u",
                     path_length_, visited_nodes_, closed_nodes_, opened_nodes_) << std::endl;
}
