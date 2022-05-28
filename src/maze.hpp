#include "matrix.hpp"


enum class maze_object
{
	wall,
	free
};

matrix<maze_object> add_walls(const matrix<maze_object>& maze);