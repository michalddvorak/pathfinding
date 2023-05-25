#pragma once

#include "pfalgorithm.hpp"
#include "../opts.hpp"

class dfs : public pf_algorithm
{
 public:
	dfs(const std::vector<opt>& options);
	void run(const maze& maze) override;
 private:
	opt_neighborhood_order neighborhood_order_;
};
