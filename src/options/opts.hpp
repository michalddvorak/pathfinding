#pragma once

#include <vector>
#include <variant>
#include "../utility/expected.hpp"
#include "../utility/utility.hpp"
#include "opt_neighborhood_order.hpp"
#include "opt_sleep_time.hpp"


using opt = std::variant<opt_neighborhood_order, opt_sleep_time>;

struct help_tag { };

struct options
{
	std::vector<opt> options;
	std::vector<std::string> nonpositional_arguments;
};

std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[]);