#include <thread>
#include <sstream>
#include <array>
#include <cstring>
#include <fstream>

#include "utility/expected.hpp"
#include "algorithms/bfs.hpp"
#include "algorithms/dfs.hpp"
#include "io/printer.hpp"
#include "opts.hpp"

template<typename T>
auto make_algorithm(const std::vector<opt>& options)
{
	return just<std::unique_ptr<pf_algorithm>>(std::make_unique<T>(options));
}


expected<std::unique_ptr<pf_algorithm>> pick_algorithm(const std::string& name, const std::vector<opt>& options)
{
	using namespace std::string_literals;
	
	auto is = [&](const char* alg) {
		return strcasecmp(name.c_str(), alg) == 0;
	};
	
	if(is("bfs"))
		return make_algorithm<bfs>(options);
	else if(is("dfs"))
		return make_algorithm<dfs>(options);
	return err<std::unique_ptr<pf_algorithm>>("unknown algorithm \""s + name + "\"");
}


void print_usage(const char* name)
{
	std::cout << "usage: " << name << " <filename> <algorithm>" << std::endl;
}

//todo: argumenty (rychlost, apod.)
//todo: další algoritmy :)

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
	auto parse_result = parse_options(argc, argv);
	if(std::holds_alternative<help_tag>(parse_result))
	{
		print_usage(argv[0]);
		return 0;
	}
	
	auto options_result = std::get<expected<options>>(parse_result);
	if(!options_result)
	{
		std::cout << "error: " << options_result.error() << std::endl;
		return 1;
	}
	auto&& [options, nonpos_arguments] = *options_result;
	
	if(nonpos_arguments.size() != 2)
	{
		print_usage(argv[0]);
		return 1;
	}
	
	
	auto maze = open_file(nonpos_arguments[0])
			.and_then(maze::load_from_stream);
	
	if(!maze)
	{
		std::cout << "error: " << maze.error() << std::endl;
		return 1;
	}
	auto algorithm = pick_algorithm(nonpos_arguments[1], options);
	
	if(!algorithm)
	{
		std::cout << "error: " << maze.error() << std::endl;
		return 1;
	}
	run(std::move(*algorithm), *maze);
	return 0;
}
