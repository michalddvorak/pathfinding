#include <queue>
#include "astar.hpp"

void astar::parse_options(const std::vector<opt>& options)
{
    visit_each(options,
               [&](const opt_neighborhood_order& opt_order)mutable { neighborhood_order_ = opt_order.order; });
}

astar::astar(const std::vector<opt>& options)
{
    parse_options(options);
}

void astar::run(const maze& maze)
{
    struct dbl_coord
    {
        double dist;
        coord vertex;
        
        bool operator<(const dbl_coord& other) const
        {
            return dist > other.dist;
        }
    };
    std::priority_queue<dbl_coord> q;
    auto [prev, seen] = fresh_all(maze);
    matrix<double> dist(prev.rows(), prev.cols(), std::numeric_limits<double>::infinity());
    
    auto open_node = [&](const coord& node, const std::optional<coord>& parent = std::nullopt)
    {
        seen(node) = true;
        dist(node) = 0;
        if (parent)
        {
            prev(node) = *parent;
            dist(node) += dist(*parent) + 1;
        }
        q.push({dist(node) + distance(node, maze.end), node});
        on_open(node);
    };
    
    open_node(maze.start);
    
    while (!q.empty())
    {
        on_step();
        auto pos = q.top();
        q.pop();
        if (pos.vertex == maze.end)
            break;
        for (auto&& neigh: neighborhood_order_ | std::views::transform([&](auto&& fn) { return fn(pos.vertex); }))
        {
            if (maze.mat.valid(neigh) &&
                maze.mat(neigh) == maze_object::free &&
                dist(pos.vertex) + 1 < dist(neigh))
            {
                on_step();
                open_node(neigh, pos.vertex);
            }
        }
        on_closed(pos.vertex);
    }
    if (seen(maze.end))
        reconstruct_path(maze, prev);
}
