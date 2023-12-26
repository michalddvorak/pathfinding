#pragma once

#include "pf_algorithm.hpp"
#include "../options/opts.hpp"

class dfs : public pf_algorithm
{
 public:
	dfs(const std::vector<opt>& options);
	void run(const maze& maze) override;
 private:
	void parse_options(const std::vector<opt>& options);
	opt_neighborhood_order neighborhood_order_;
};
