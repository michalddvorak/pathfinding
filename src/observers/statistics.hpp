#pragma once
#include <vector>
#include "../options/opts.hpp"
#include "../algorithms/pf_algorithm.hpp"

class statistics
{
  private:
    auto open_callback()
    {
        return [&](const coord&)
        {
            ++opened_nodes_;
            ++visited_nodes_;
        };
    }
    auto closed_callback()
    {
        return [&](const coord&)
        {
            ++closed_nodes_;
            ++visited_nodes_;
        };
    }
    auto path_callback()
    {
        return [&](const coord&)
        {
            ++path_length_;
        };
    }
  
  public:
    statistics(pf_algorithm* algorithm);
    void print_statistics();
    
    void reset()
    {
        opened_nodes_ = 0;
        closed_nodes_ = 0;
        visited_nodes_ = 0;
        path_length_ = 0;
    }
  
  private:
    unsigned opened_nodes_ = 0;
    unsigned closed_nodes_ = 0;
    unsigned visited_nodes_ = 0;
    unsigned path_length_ = 0;
    
};
