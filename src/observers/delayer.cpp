#include "delayer.hpp"

#include "../utility/overload.hpp"

void delayer::parse_options(const std::vector<opt>& options)
{
	for(const auto& option: options)
		std::visit(overload {
				[&](const opt_sleep_time& sleep_time)mutable { sleep_duration_ = sleep_time.duration; },
		}, option);
}
delayer::delayer(pf_algorithm* algorithm, const std::vector<opt>& options) : algorithm_ {algorithm}
{
	parse_options(options);
	algorithm->register_step(step_callback());
}