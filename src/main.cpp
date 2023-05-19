#include <thread>
#include <sstream>
#include <array>
#include <cstring>
#include <fstream>

#include "utility/expected.hpp"
#include "algorithms/bfs.hpp"
#include "algorithms/dfs.hpp"
#include "io/printer.hpp"

expected<std::unique_ptr<pf_algorithm>> pick_algorithm(const char* name)
{
	using namespace std::string_literals;
	
	auto is = [&](const char* alg) {
		return strcasecmp(name, alg) == 0;
	};
	
	if(is("bfs"))
		return just<std::unique_ptr<pf_algorithm>>(std::make_unique<bfs>());
	else if(is("dfs"))
		return just<std::unique_ptr<pf_algorithm>>(std::make_unique<dfs>());
	//todo: more
	return err<std::unique_ptr<pf_algorithm>>("unknown algorithm \""s + name + "\"");
}

void print_usage(const char* name)
{
	std::cout << "usage: " << name << " <filename> <algorithm>" << std::endl;
}

//todo: argumenty (rychlost, apod.)
//todo: další algoritmy :)
//todo: umožnit změnit pořadí procházení sousedů (bfs i dfs)

expected<std::ifstream> open_file(const std::string& filename)
{
	std::ifstream ifs {filename};
	if(!ifs.is_open())
		return err<std::ifstream>("Could not open file \"" + filename + "\"");
	return just(std::move(ifs));
}

void run(std::unique_ptr<pf_algorithm> algorithm, const maze& maze)
{
	//todo statistiky
	
	printer p(&maze, algorithm.get());
	p.clear();
	p.print_maze();
	algorithm->run(maze);
	p.set_cursor({maze.mat.rows(), 0});
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		print_usage(argv[0]);
		return 1;
	}
	
	auto maze = open_file(argv[1])
			.and_then(maze::load_from_stream);
	
	if(!maze)
	{
		std::cout << "error: " << maze.error();
		return 1;
	}
	auto algorithm = pick_algorithm(argv[2]);
	
	if(!algorithm)
	{
		std::cout << "error: " << maze.error();
		return 1;
	}
	run(std::move(*algorithm), *maze);
	return 0;
}
