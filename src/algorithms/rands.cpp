#include "rands.hpp"

void rands::parse_options(const std::vector<opt>& options)
{
    visit_each(options,
               [&](const opt_neighborhood_order& opt_order)mutable { neighborhood_order_ = opt_order.order; },
               [&](const opt_seed& opt_seed) mutable { rng.seed(opt_seed.seed); });
}

rands::rands(const std::vector<opt>& options)
{
    parse_options(options);
}

void rands::run(const maze& maze)
{
    std::vector<coord> q;
    auto [prev, seen] = fresh_all(maze);
    auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt)
    {
        q.push_back(node);
        seen(node) = true;
        if (parent)
            prev(node) = *parent;
        on_open(node);
    };
    
    open_node(maze.start);
    
    while (!q.empty())
    {
        on_step();
        auto pos = erase_random(q);
        if (pos == maze.end)
            break;
        for (auto&& neigh: neighborhood_order_ | std::views::transform([&](auto&& fn) { return fn(pos); }))
        {
            if (maze.mat.valid(neigh) && !seen(neigh) && maze.mat(neigh) == maze_object::free)
            {
                on_step();
                open_node(neigh, pos);
            }
        }
        on_closed(pos);
    }
    if (seen(maze.end))
        reconstruct_path(maze, prev);
}
