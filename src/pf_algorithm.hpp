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

class pf_algorithm : public observable<algorithm_state, coord>,
					 public observable<const maze&>
{
 public:
	pf_algorithm(maze maze);
	virtual void run() = 0;
 protected:
	maze m_maze;
	matrix<algorithm_state> m_state;
};