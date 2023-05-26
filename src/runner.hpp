#pragma once


#include "io/printer.hpp"

class runner
{
 public:
	runner(std::unique_ptr<pf_algorithm> algorithm, const maze& maze, const std::vector<opt>& options);
	void run()
	{
		printer_.clear();
		printer_.print_maze();
		algorithm_->run(maze_);
		printer_.set_cursor({maze_.mat.rows(), 0});
	}
 private:
	std::unique_ptr<pf_algorithm> algorithm_;
	maze maze_;
	printer printer_;
};
