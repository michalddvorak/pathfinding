#include "pfalgorithm.hpp"

void pf_algorithm::reconstruct_path(const maze& maze, const matrix<coord>& prev)
{
	auto cur = maze.end;
	on_step();
	on_path(cur);
	while(true)
	{
		if(cur == maze.start)
			break;
		cur = prev(cur);
		on_step();
		on_path(cur);
	}
}
std::pair<pf_algorithm::prev_matrix, pf_algorithm::seen_matrix> pf_algorithm::fresh_all(const maze& maze)
{
	matrix<coord> prev(maze.mat.rows(), maze.mat.cols());
	matrix<int8_t> seen(maze.mat.rows(), maze.mat.cols(), false);
	for(size_t i = 0; i < maze.mat.rows(); ++i)
		for(size_t j = 0; j < maze.mat.cols(); ++j)
			if(maze.mat({i, j}) == maze_object::free)
				on_fresh(coord {i, j});
	return {std::move(prev), std::move(seen)};
}
