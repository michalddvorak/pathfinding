#include "bfs.hpp"
#include <queue>

void bfs::run()
{
	std::queue<coord> q;
	matrix<coord> prev(maze_.mat.rows(), maze_.mat.cols());
	matrix<int8_t> seen(maze_.mat.rows(), maze_.mat.cols(), false);
	for(size_t i = 0; i < maze_.mat.rows(); ++i)
		for(size_t j = 0; j < maze_.mat.cols(); ++j)
			if(maze_.mat({i, j}) == maze_object::free)
				on_fresh(coord {i, j});
	
	auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt) {
		q.push(node);
		seen(node) = true;
		if(parent)
			prev(node) = *parent;
		on_open(node);
	};
	
	open_node(maze_.start);
	
	while(!q.empty())
	{
		on_step();
		auto pos = q.front();
		q.pop();
		if(pos == maze_.end)
			break;
		for(auto&& neigh: {pos.left(), pos.right(), pos.up(), pos.down()})
		{
			if(maze_.mat.valid(neigh) && !seen(neigh) && maze_.mat(neigh) == maze_object::free)
			{
				on_step();
				open_node(neigh, pos);
			}
		}
		on_closed(pos);
	}
	if(seen(maze_.end))
		reconstruct_path(prev);
}
