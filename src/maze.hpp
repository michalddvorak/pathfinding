#include <iostream>
#include "matrix.hpp"


enum class maze_object
{
	wall,
	free
};

struct coord
{
	size_t i, j;
};

struct maze
{
	static maze read_from_stream(std::istream& is);
	matrix<maze_object> m_mat;
	coord m_start;
	coord m_end;
};

