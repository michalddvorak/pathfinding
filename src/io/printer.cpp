
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
				[&](const opt_sleep_time& sleep_time)mutable { sleep_duration_ = std::chrono::milliseconds(sleep_time.amount); },
				[](auto&&) { }
		}, option);
}
