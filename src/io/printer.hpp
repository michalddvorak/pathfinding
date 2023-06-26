#pragma once

#include <string>
#include <memory>
#include <thread>
#include <sstream>

#include "../algorithms/pf_algorithm.hpp"
#include "term.hpp"
#include "../utility/event.hpp"

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
	
	const maze* maze_;
	const pf_algorithm* algorithm_;
};