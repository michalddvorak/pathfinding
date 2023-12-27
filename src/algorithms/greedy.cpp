#include <queue>
#include "greedy.hpp"
#include <ranges>
void greedy::parse_options(const std::vector<opt>& options)
{
    visit_each(options,
               [&](const opt_neighborhood_order& opt_order)mutable { neighborhood_order_ = opt_order.order; });
}

greedy::greedy(const std::vector<opt>& options)
{
    parse_options(options);
}

void greedy::run(const maze& maze)
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
        q.push({distance(node, maze.end), node});
        on_open(node);
    };
    
    open_node(maze.start);
    on_step();
    
    while (!q.empty())
    {
        auto pos = q.top();
        q.pop();
        on_explore(pos.vertex);
        on_step();
        if (pos.vertex == maze.end)
            break;
        for (auto&& neigh : neighborhood_order_ | std::views::transform([&](auto&& fn) { return fn(pos.vertex); }))
        {
            if (maze.mat.valid(neigh) &&
                maze.mat(neigh) == maze_object::free &&
                dist(pos.vertex) + 1 < dist(neigh))
            {
                open_node(neigh, pos.vertex);
                on_step();
            }
        }
        on_closed(pos.vertex);
        on_step();
    }
    if (seen(maze.end))
        reconstruct_path(maze, prev);
}

std::string greedy::description() const
{
    return "Greedy Search";
}
