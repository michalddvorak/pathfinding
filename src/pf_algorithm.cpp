#include "pf_algorithm.hpp"

pf_algorithm::pf_algorithm(maze maze) : m_maze(std::move(maze)),
										m_state(m_maze.m_mat.rows(), m_maze.m_mat.cols()) { }
