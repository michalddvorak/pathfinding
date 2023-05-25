#pragma once

#include "pfalgorithm.hpp"
#include "../opts.hpp"

class bfs : public pf_algorithm
{
 public:
	void run(const maze& maze) override;
	bfs(const std::vector<opt>& options);
 private:
	opt_neighborhood_order neighborhood_order_;
};