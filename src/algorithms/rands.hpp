#pragma once

#include <random>
#include "pf_algorithm.hpp"

class rands : public pf_algorithm
{
  public:
    rands(const std::vector<opt>& options);
    
    void run(const maze& maze) override;
  
  private:
    template <typename T>
    T erase_random(std::vector<T>& v)
    {
        if (v.empty())
            throw std::invalid_argument("Empty vector");
        auto dist = std::uniform_int_distribution<size_t>(0, v.size() - 1);
        size_t random_index = dist(rng);
        T ret = std::move(v[random_index]);
        v.erase(v.begin() + random_index);
        return ret;
    }
    std::string description() const override;
    void parse_options(const std::vector<opt>& opt_seed);
    
    
    std::mt19937 rng;
};
