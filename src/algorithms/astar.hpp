#pragma once

#include "pf_algorithm.hpp"
#include "../options/opts.hpp"

class astar : public pf_algorithm
{
  public:
    void run(const maze& maze) override;
    
    astar(const std::vector<opt>& options);
  
  private:
    void parse_options(const std::vector<opt>& options);
    
    opt_neighborhood_order neighborhood_order_;
    std::function<double(const coord&, const coord&)> distance =
            [](const coord& a, const coord& b) -> double
            {
                return llabs((ssize_t)a.i - (ssize_t)b.i) + llabs((ssize_t)a.j - (ssize_t)b.j);
            };
};