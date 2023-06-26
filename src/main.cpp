#include <thread>
#include <sstream>
#include <array>

#include "utility/expected.hpp"
#include "algorithms/bfs.hpp"
#include "algorithms/dfs.hpp"
#include "options/opts.hpp"
#include "runner.hpp"


expected<std::unique_ptr<pf_algorithm>> pick_algorithm(const std::string& name, const std::vector<opt>& options)
{
	using namespace std::string_literals;
	
	if(equals_insensitive(name, "bfs"))
		return pf_algorithm::make<bfs>(options);
	else if(equals_insensitive(name, "dfs"))
		return pf_algorithm::make<dfs>(options);
	return err<std::unique_ptr<pf_algorithm>>("unknown algorithm \""s + name + "\"");
}


void print_usage(const char* name)
{
	//TODO: lepší
	std::cout << "usage: " << name << " <filename> <algorithm> [-n|--neighborhood] (lrud)" << std::endl;
}

//todo: unit testy
//todo: statistiky (počet otevřených nodů, délka cesty ...)
//todo: další algoritmy :)



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
		std::cout << "error parsing options: " << options_result.error() << std::endl;
		return 1;
	}
	
	if(options_result->nonpositional_arguments.size() != 2)
	{
		print_usage(argv[0]);
		return 1;
	}
	
	auto maze = open_file(options_result->nonpositional_arguments[0])
			.and_then(maze::load_from_stream);
	
	if(!maze)
	{
		std::cout << "error loading the maze: " << maze.error() << std::endl;
		return 1;
	}
	auto algorithm = pick_algorithm(options_result->nonpositional_arguments[1], options_result->options);
	
	if(!algorithm)
	{
		std::cout << "error picking algorithm: " << algorithm.error() << std::endl;
		return 1;
	}
	runner r(std::move(*algorithm), *maze, options_result->options);
	r.run();
	return 0;
}
