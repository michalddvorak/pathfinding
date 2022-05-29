#pragma once

#include "observable.hpp"
#include "maze.hpp"

enum class algorithm_state
{
	fresh,
	open,
	closed,
	start,
	end,
	path
};

class pf_algorithm
{
 public:
	pf_algorithm(maze maze);
	virtual void run() = 0;
	event<algorithm_state, coord, const maze&> change;
	event<const maze&> start;
 protected:
	maze m_maze;
	matrix<algorithm_state> m_state;
};