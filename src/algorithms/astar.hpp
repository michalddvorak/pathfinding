#pragma once

#include "pf_algorithm.hpp"
#include "../options/opts.hpp"

class astar : public pf_algorithm
{
  public:
    void run(const maze& maze) override;
    
    astar(const std::vector<opt>& options);
    std::string description() const override;
  
  private:
    void parse_options(const std::vector<opt>& opt_order);
    
    std::function<double(const coord&, const coord&)> distance =
            [](const coord& a, const coord& b) -> double
            {
                return llabs((ssize_t)a.i - (ssize_t)b.i) + llabs((ssize_t)a.j - (ssize_t)b.j);
            };
};