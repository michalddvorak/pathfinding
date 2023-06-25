#pragma once


#include "io/printer.hpp"

class runner
{
 public:
	runner(std::unique_ptr<pf_algorithm> algorithm, const maze& maze, const std::vector<opt>& options);
	void run();
 private:
	std::unique_ptr<pf_algorithm> algorithm_;
	maze maze_;
	printer printer_;
};
