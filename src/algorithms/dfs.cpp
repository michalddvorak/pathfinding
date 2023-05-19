#include "dfs.hpp"
#include <stack>

void dfs::run(const maze& maze)
{
	std::array neighborhoods = {&coord::left, &coord::up, &coord::right, &coord::down};
	using iter = decltype(neighborhoods.begin());
	std::stack<std::tuple<coord, iter, iter>> q;
	
	auto [prev, seen] = fresh_all(maze);
	
	auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt) {
		q.emplace(node, neighborhoods.begin(), neighborhoods.end());
		seen(node) = true;
		if(parent)
			prev(node) = *parent;
		on_open(node);
	};
	
	open_node(maze.start);
	
	while(!q.empty())
	{
		on_step();
		auto& [pos, begin, end] = q.top();
		if(pos == maze.end)
			break;
		if(begin != end)
		{
			auto neigh = (pos.*(*begin++))();
			if(maze.mat.valid(neigh) && !seen(neigh) && maze.mat(neigh) == maze_object::free)
			{
				on_step();
				open_node(neigh, pos);
			}
			continue;
		}
		on_closed(pos);
		q.pop();
	}
	if(seen(maze.end))
		reconstruct_path(maze, prev);
}
