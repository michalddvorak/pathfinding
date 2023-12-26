#include "runner.hpp"

runner::runner(std::unique_ptr<pf_algorithm> algorithm, const maze& maze, const std::vector<opt>& options) : algorithm_ {std::move(algorithm)},
																											 maze_ {maze},
																											 printer_ {&maze_, algorithm_.get(), options},
																											 delayer_(algorithm_.get(), options) { }
void runner::run()
{
	printer_.clear();
	printer_.print_maze();
	algorithm_->run(maze_);
	printer_.set_cursor({maze_.mat.rows(), 0});
}
