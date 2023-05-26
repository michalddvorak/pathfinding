#pragma once

#include <vector>
#include <variant>
#include <map>
#include "coord.hpp"
#include "utility/expected.hpp"
#include "utility/utility.hpp"


struct opt_neighborhood_order
{
	expected<void> set_permutation(const std::string& order)
	{
		using namespace std::string_literals;
		const std::map<char, coord(coord::*)() const> fns =
				{
						{'l', &coord::left},
						{'r', &coord::right},
						{'u', &coord::up},
						{'d', &coord::down}
				};
		if(!is_same_up_to_permutation(order, "lrud"))
			return err("invalid permutation \""s + order + "\"");
		
		std::transform(order.begin(), order.end(), ord.begin(),
					   [&](char c) { return fns.at(c); });
		return true;
	}
	const std::array<coord(coord::*)() const, 4>& get_order() const
	{
		return ord;
	}
 private:
	std::array<coord(coord::*)() const, 4> ord = {&coord::left, &coord::down, &coord::right, &coord::up};
};

struct opt_sleep_time
{
	unsigned int amount;
};


using opt = std::variant<opt_neighborhood_order, opt_sleep_time>;

struct help_tag { };

using options = std::pair<std::vector<opt>, std::vector<std::string>>;


std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[]);