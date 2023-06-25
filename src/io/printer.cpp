
#include "printer.hpp"
#include "../utility/overload.hpp"

printer::printer(const maze* maze, pf_algorithm* algorithm, const std::vector<opt>& options) : maze_ {maze}, algorithm_ {algorithm}
{
	parse_options(options);
	algorithm->register_path(path_callback());
	algorithm->register_step(step_callback());
	algorithm->register_fresh(fresh_callback());
	algorithm->register_closed(closed_callback());
	algorithm->register_open(open_callback());
}
void printer::parse_options(const std::vector<opt>& options)
{
	for(const auto& option: options)
		std::visit(overload {
				[&](const opt_sleep_time& sleep_time)mutable { sleep_duration_ = sleep_time.duration; },
		}, option);
}
void printer::print_maze()
{
	set_cursor({0, 0});
	for(size_t i = 0; i < maze_->mat.rows(); ++i)
	{
		for(size_t j = 0; j < maze_->mat.cols(); ++j)
		{
			set_cursor({i, j});
			switch(maze_->mat(i, j))
			{
				case maze_object::wall:
					std::cout << 'X';
					break;
				case maze_object::free:
					std::cout << ' ';
					break;
			}
		}
		std::cout << '\n';
	}
	print(maze_->start, with_fg_color(255, 255, 0)("S"));
	print(maze_->end, with_fg_color(255, 255, 0)("E"));
}
