#include <sstream>
#include "maze.hpp"


maze maze::read_from_stream(std::istream& is)
{
	using namespace std::string_literals;
	size_t rows, cols, starti, startj, endi, endj;
	std::string line;
	std::stringstream ss;
	
	auto get_ln = [&](const std::string& err_msg) {
		if(!std::getline(is, line))
			throw std::invalid_argument(err_msg);
		ss.str(line);
	};
	
	get_ln("Could not parse dimensions");
	
	if(!(ss >> rows >> cols))
		throw std::invalid_argument("Invalid dimensions: \""s + line + "\"");
	get_ln("Could not parse start coords");
	if(!(ss >> starti >> startj >> endi >> endj))
		throw std::invalid_argument("Invalid start coords: \""s + line + "\"");
	if(starti >= rows)
		throw std::invalid_argument("Row start index out of range");
	if(startj >= cols)
		throw std::invalid_argument("Column start index out of range");
	if(endi >= rows)
		throw std::invalid_argument("Row end index out of range");
	if(endj >= cols)
		throw std::invalid_argument("Column end index out of range");
	
	
	maze result_maze {matrix<maze_object> {rows, cols}, {starti, startj}, {endi, endj}};
	
	for(size_t i = 0; i < rows; ++i)
	{
		get_ln("Could not read row number "s + std::to_string(i));
		if(line.size() != cols)
			throw std::invalid_argument("Invalid size of row number "s + std::to_string(i) + ", expected size: " + std::to_string(cols) + "got size: " + std::to_string(line.size()));
		for(size_t j = 0; j < cols; ++j)
			if(!isblank(line[j]))
				result_maze.m_mat[i][j] = maze_object::wall;
			else
				result_maze.m_mat[i][j] = maze_object::free;
	}
	
	return result_maze;
}