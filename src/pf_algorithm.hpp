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


class pf_algorithm : public observable<pf_algorithm, size_t, size_t>
{
 public:
	virtual ~pf_algorithm() = default;
	pf_algorithm(const matrix<maze_object>& maze);
	virtual void run() = 0;
	const matrix<maze_object>& get_maze() const;
	const matrix<algorithm_state>& get_state() const;
 protected:
	matrix<maze_object> m_maze;
	matrix<algorithm_state> m_state;
};