#pragma once


#include "io/printer.hpp"
#include "observers/delayer.hpp"
#include "observers/statistics.hpp"

class runner
{
 public:
	runner(std::unique_ptr<pf_algorithm> algorithm, const maze& maze, const std::vector<opt>& options);
	void run();
 private:
	std::unique_ptr<pf_algorithm> algorithm_;
	maze maze_;
	printer printer_;
	delayer delayer_;
    statistics statistic_;
};
