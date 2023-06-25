#include "dfs.hpp"
#include <stack>

#include "../utility/overload.hpp"

void dfs::run(const maze& maze)
{
	
	using iter = decltype(std::begin(neighborhood_order_.order));
	std::stack<std::tuple<coord, iter, iter>> q;
	
	auto [prev, seen] = fresh_all(maze);
	
	auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt) {
		q.emplace(node, std::begin(neighborhood_order_.order), std::end(neighborhood_order_.order));
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
			auto neigh = (*begin++)(pos);
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
dfs::dfs(const std::vector<opt>& options)
{
	parse_options(options);
}
void dfs::parse_options(const std::vector<opt>& options)
{
	for(const auto& option: options)
		std::visit(overload {
				[&](const opt_neighborhood_order& order)mutable { neighborhood_order_ = order; },
		}, option);
}
