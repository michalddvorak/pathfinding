#pragma once

#include "pf_algorithm.hpp"
#include "../options/opts.hpp"

class dfs : public pf_algorithm
{
 public:
	dfs(const std::vector<opt>& options);
	void run(const maze& maze) override;
    std::string description() const override;
 private:
	void parse_options(const std::vector<opt>& options);
};
