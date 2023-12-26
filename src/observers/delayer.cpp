#include "delayer.hpp"

void delayer::parse_options(const std::vector<opt>& options)
{
	visit_each(options,
			   [&](const opt_sleep_time& sleep_time)mutable { sleep_duration_ = sleep_time.duration; });
}
delayer::delayer(pf_algorithm* algorithm, const std::vector<opt>& options) : algorithm_ {algorithm}
{
	parse_options(options);
	algorithm->register_step(step_callback());
}