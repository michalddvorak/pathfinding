#pragma once

#include <iostream>
#include "matrix.hpp"
#include "utility/expected.hpp"

enum class maze_object
{
	wall,
	free
};

struct maze
{
	static expected<maze> load_from_stream(std::istream&& is);
	matrix<maze_object> mat;
	coord start;
	coord end;
};
