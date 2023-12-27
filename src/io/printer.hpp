#pragma once

#include <string>
#include <memory>
#include <thread>
#include <sstream>

#include "../algorithms/pf_algorithm.hpp"
#include "term.hpp"
#include "../utility/event.hpp"

class printer : public term
{
  private:
    auto path_callback()
    {
        return [&](const coord& p)
        {
            if (p != maze_->start && p != maze_->end)
                print(p, PATH);
        };
    }
    
    auto open_callback()
    {
        return [&](const coord& p)
        {
            if (p != maze_->start && p != maze_->end)
                print(p, OPEN);
        };
    }
    
    auto closed_callback()
    {
        return [&](const coord& p)
        {
            if (p != maze_->start && p != maze_->end)
                print(p, CLOSED);
        };
    }
    
    auto fresh_callback()
    {
        return [&](const coord& p)
        {
            if (p != maze_->start && p != maze_->end)
                print(p, " ");
        };
    }
    
    auto explore_callback()
    {
        return [&](const coord& p)
        {
            if (p != maze_->start && p != maze_->end)
                print(p, EXPLORING);
        };
    }
  
  public:
    printer(const maze* maze, pf_algorithm* algorithm, const std::vector<opt>& options);
    
    void print_description();
    void print_maze();
  
  private:
    void parse_options(const std::vector<opt>& options);
    const static std::string EXPLORING;
    const static std::string OPEN;
    const static std::string CLOSED;
    const static std::string START;
    const static std::string END;
    const static std::string WALL;
    const static std::string PATH;
    const maze* maze_;
    const pf_algorithm* algorithm_;
};