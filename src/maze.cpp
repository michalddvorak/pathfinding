#include <sstream>
#include "maze.hpp"

expected<std::stringstream> read_line(std::istream& is, const std::string& err_msg = "")
{
	std::string line;
	if(!std::getline(is, line))
		return err<std::stringstream>(err_msg);
	return just(std::stringstream {line});
}

expected<void> parse_dimensions(std::stringstream&& ss, size_t& rows, size_t& cols)
{
	using namespace std::string_literals;
	if(!(ss >> rows >> cols))
		return err("invalid dimensions: \""s + ss.str() + "\"");
	return just();
}
expected<void> parse_start_end(std::stringstream&& ss, size_t& starti, size_t& startj, size_t& endi, size_t& endj)
{
	using namespace std::string_literals;
	if(!(ss >> starti >> startj >> endi >> endj))
		return err("invalid start/end coords: \""s + ss.str() + "\"");
	return just();
}
expected<maze> check_dims(size_t starti, size_t startj, size_t endi, size_t endj, size_t rows, size_t cols)
{
	if(starti >= rows)
		return err<maze>("row start index out of range");
	if(startj >= cols)
		return err<maze>("column start index out of range");
	
	if(endi >= rows)
		return err<maze>("row end index out of range");
	if(endj >= cols)
		return err<maze>("column end index out of range");
	return just(maze {{rows,   cols},
					  {starti, startj},
					  {endi,   endj}});
}

expected<maze> read_maze(maze&& _maze, std::istream& is)
{
	using namespace std::string_literals;
	for(size_t i = 0; i < _maze.mat.rows(); ++i)
	{
		auto r = read_line(is, "could not read row number "s + std::to_string(i))
				.and_then([&](std::stringstream&& ss) {
					auto&& line = ss.str();
					if(line.size() != _maze.mat.cols())
						return err("invalid size of row number "s + std::to_string(i) + ", expected size: " + std::to_string(_maze.mat.cols()) + "got size: " + std::to_string(line.size()));
					for(size_t j = 0; j < _maze.mat.cols(); ++j)
						if(!isblank(line[j]))
							_maze.mat[i][j] = maze_object::wall;
						else
							_maze.mat[i][j] = maze_object::free;
					return just();
				});
		if(!r)
			return err<maze>(std::move(r.error()));
	}
	return just(std::move(_maze));
}


expected<maze> maze::load_from_stream(std::istream&& is)
{
	size_t rows, cols, starti, startj, endi, endj;
	return read_line(is, "could not parse_options dimensions")
			.and_then(parse_dimensions, rows, cols)
			.and_then(read_line, is, "could not parse_options start coords")
			.and_then(parse_start_end, starti, startj, endi, endj)
			.and_then(check_dims, starti, startj, endi, endj, rows, cols)
			.and_then(read_maze, is);
}
