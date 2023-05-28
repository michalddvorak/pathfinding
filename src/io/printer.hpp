#pragma once

#include <string>
#include <memory>
#include <thread>
#include <sstream>

#include "../algorithms/pfalgorithm.hpp"
#include "term.hpp"
#include "../utility/event.hpp"

using namespace std::chrono_literals;
class printer : public term
{
 private:
	auto path_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_blink()(with_fg_color(0, 0, 255)("o")));
		};
	}
	auto step_callback()
	{
		return [&]() {
			std::this_thread::sleep_for(sleep_duration_);
		};
	}
	auto open_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_fg_color(255, 0, 0)("O"));
		};
	}
	auto closed_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_fg_color(255, 0, 255)("#"));
		};
	}
	auto fresh_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, ".");
		};
	}
 public:
	printer(const maze* maze, pf_algorithm* algorithm, const std::vector<opt>& options);
	void print_maze();
 private:
	void parse_options(const std::vector<opt>& options);
	std::chrono::milliseconds sleep_duration_ = 15ms;
	
	const maze* maze_;
	const pf_algorithm* algorithm_;
};