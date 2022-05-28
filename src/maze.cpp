#include "maze.hpp"

matrix<maze_object> add_walls(const matrix<maze_object>& maze)
{
	matrix<maze_object> new_maze(maze.rows() + 2, maze.cols() + 2);
	for(size_t i = 0; i < new_maze.rows(); ++i)
		for(size_t j = 0; j < new_maze.cols(); ++j)
		{
			if(i == 0 ||
			   j == 0 ||
			   i == new_maze.rows() - 1 ||
			   j == new_maze.cols() - 1)
				new_maze[i][j] = maze_object::wall;
			else
				new_maze[i][j] = maze[i - 1][j - 1];
		}
	return new_maze;
}