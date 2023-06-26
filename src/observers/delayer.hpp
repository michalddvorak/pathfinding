#pragma once
#include <thread>
#include <vector>
#include "../options/opts.hpp"
#include "../algorithms/pf_algorithm.hpp"

class delayer
{
 private:
	auto step_callback()
	{
		return [&]() {
			std::this_thread::sleep_for(sleep_duration_);
		};
	}
 public:
	delayer(pf_algorithm* algorithm, const std::vector<opt>& options);
 private:
	void parse_options(const std::vector<opt>& options);
	std::chrono::milliseconds sleep_duration_ = std::chrono::milliseconds(15);
	const pf_algorithm * algorithm_;
};
