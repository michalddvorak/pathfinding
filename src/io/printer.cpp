
#include "printer.hpp"

printer::printer(const maze* maze, pf_algorithm* algorithm) : maze_{maze}, algorithm_{algorithm}
{
	algorithm_->register_path(path_callback());
	algorithm_->register_step(step_callback());
	algorithm_->register_fresh(fresh_callback());
	algorithm_->register_closed(closed_callback());
	algorithm_->register_open(open_callback());
}
