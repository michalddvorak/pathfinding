#include "pf_algorithm.hpp"

pf_algorithm::pf_algorithm(const matrix<maze_object>& maze) : m_maze(add_walls(maze)),
															  m_state(m_maze.rows(), m_maze.cols()) { }
const matrix<maze_object>& pf_algorithm::get_maze() const
{
	return m_maze;
}
const matrix<algorithm_state>& pf_algorithm::get_state() const
{
	return m_state;
}
