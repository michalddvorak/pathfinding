#pragma once

#include <string>
#include "../utility/expected.hpp"
#include "../coord.hpp"

struct opt_neighborhood_order
{
	std::array<std::function<coord(const coord&)>, 4> order = {&coord::left, &coord::down, &coord::right, &coord::up};
};
