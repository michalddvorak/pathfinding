#include "bfs.hpp"
#include "../utility/overload.hpp"
#include <queue>

void bfs::run(const maze& maze)
{
	std::queue<coord> q;
	auto [prev, seen] = fresh_all(maze);
	
	auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt) {
		q.push(node);
		seen(node) = true;
		if(parent)
			prev(node) = *parent;
		on_open(node);
	};
	
	open_node(maze.start);
	
	while(!q.empty())
	{
		on_step();
		auto pos = q.front();
		q.pop();
		if(pos == maze.end)
			break;
		for(auto&& neigh_fn: neighborhood_order_.get_order())
		{
			auto&& neigh = (pos.*neigh_fn)();
			if(maze.mat.valid(neigh) && !seen(neigh) && maze.mat(neigh) == maze_object::free)
			{
				on_step();
				open_node(neigh, pos);
			}
		}
		on_closed(pos);
	}
	if(seen(maze.end))
		reconstruct_path(maze, prev);
}
bfs::bfs(const std::vector<opt>& options)
{
	for(const auto& option: options)
		std::visit(overload {
				[&](const opt_neighborhood_order& order)mutable { neighborhood_order_ = order; },
				[](auto&&) { }
		}, option);
}
