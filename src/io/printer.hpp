#pragma once

#include <string>
#include <memory>
#include <thread>
#include <sstream>

#include "../algorithms/pfalgorithm.hpp"
#include "term.hpp"
#include "../utility/event.hpp"

class printer : public term
{
 private:
	auto path_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_blink(with_color(0, 0, 255, "o")));
		};
	}
	auto step_callback()
	{
		return []() {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(15ms);
		};
	}
	auto open_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_color(255, 0, 0, "O"));
		};
	}
	auto closed_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, with_color(255, 0, 255, "#"));
		};
	}
	auto fresh_callback()
	{
		return [&](const coord& p) {
			if(p != maze_->start && p != maze_->end)
				print(p, " ");
		};
	}
 public:
	printer(const maze * maze, pf_algorithm * algorithm);
	void print_maze()
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
		print(maze_->start, with_color(255, 255, 0, "S"));
		print(maze_->end, with_color(255, 255, 0, "E"));
	}
 private:
	const maze * maze_;
	pf_algorithm * algorithm_;
};