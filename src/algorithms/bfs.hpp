#pragma once

#include "pf_algorithm.hpp"
#include "../options/opts.hpp"

class bfs : public pf_algorithm
{
 public:
	void run(const maze& maze) override;
	bfs(const std::vector<opt>& options);
    std::string description() const override;
 private:
	void parse_options(const std::vector<opt>& opt_order);
};