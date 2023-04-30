#include <thread>
#include <sstream>
#include <array>
#include <cstring>
#include <fstream>

#include "expected.hpp"
#include "term.hpp"
#include "bfs.hpp"

struct printer
{
 private:
	auto path_callback()
	{
		return [&](const coord& p) {
			if(p != algorithm_->get_maze().start && p != algorithm_->get_maze().end)
				print(p, with_blink(with_color(0, 0, 255, "o")));
		};
	}
	auto step_callback()
	{
		return []() {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(15ms);
		};
	}
	auto open_callback()
	{
		return [&](const coord& p) {
			if(p != algorithm_->get_maze().start && p != algorithm_->get_maze().end)
				print(p, with_color(255, 0, 0, "O"));
		};
	}
	auto closed_callback()
	{
		return [&](const coord& p) {
			if(p != algorithm_->get_maze().start && p != algorithm_->get_maze().end)
				print(p, with_color(255, 0, 255, "#"));
		};
	}
	auto fresh_callback()
	{
		return [&](const coord& p) {
			if(p != algorithm_->get_maze().start && p != algorithm_->get_maze().end)
				print(p, " ");
		};
	}
 public:
	printer(std::unique_ptr<pf_algorithm> algo) : algorithm_(std::move(algo))
	{
		algorithm_->register_path(path_callback());
		algorithm_->register_step(step_callback());
		algorithm_->register_fresh(fresh_callback());
		algorithm_->register_closed(closed_callback());
		algorithm_->register_open(open_callback());
	}
	void run()
	{
		clear();
		print_maze();
		algorithm_->run();
		set_cursor({algorithm_->get_maze().mat.rows(), 0});
	}
 private:
	template<typename ...Args>
	void print(const coord& p, Args&& ... args)
	{
		set_cursor(p);
		(std::cout << ... << args).flush();
	}
	std::string with_color(int r, int g, int b, const std::string& what)
	{
		return color_fg(r, g, b) + what + ATTR_END;
	}
	std::string with_blink(const std::string& what)
	{
		return BLINK + what + ATTR_END;
	}
	
	void clear()
	{
		std::cout << "\033[2J";
	}
	void print_maze()
	{
		set_cursor({0, 0});
		for(size_t i = 0; i < algorithm_->get_maze().mat.rows(); ++i)
		{
			for(size_t j = 0; j < algorithm_->get_maze().mat.cols(); ++j)
			{
				set_cursor({i, j});
				switch(algorithm_->get_maze().mat(i, j))
				{
					case maze_object::wall:
						std::cout << 'X';
						break;
					case maze_object::free:
						std::cout << ' ';
						break;
				}
			}
			std::cout << '\n';
		}
		print(algorithm_->get_maze().start, with_color(255, 255, 0, "S"));
		print(algorithm_->get_maze().end, with_color(255, 255, 0, "E"));
	}
	static constexpr const char* ATTR_END = "\033[0m";
	static constexpr const char* BLINK = "\033[5m";
	
	
	std::string color_bg(int r, int g, int b)
	{
		std::stringstream ss;
		ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
		std::string res;
		ss >> res;
		return res;
	}
	
	std::string color_fg(int r, int g, int b)
	{
		std::stringstream ss;
		ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
		std::string res;
		ss >> res;
		return res;
	}
	
	void set_cursor(const coord& p)
	{
		std::cout << "\033[" << p.i + 1 << ';' << p.j + 1 << 'H';
	}
	term t;
	std::unique_ptr<pf_algorithm> algorithm_;
};

expected<std::unique_ptr<pf_algorithm>> pick_algorithm(maze&& maze, const char* name)
{
	using namespace std::string_literals;
	
	auto is = [&](const char* alg) {
		return strcasecmp(name, alg) == 0;
	};
	
	if(is("bfs"))
		return just<std::unique_ptr<pf_algorithm>>(std::make_unique<bfs>(std::move(maze)));
	//todo: more
	return err<std::unique_ptr<pf_algorithm>>("unknown algorithm \""s + name + "\"");
}

void print_usage(const char* name)
{
	std::cout << "usage: " << name << " <filename> <algorithm>" << std::endl;
}

//todo: statistiky
//todo: argumenty (rychlost, apod.)
//todo: konfigurák
//todo: další algoritmy :)

expected<std::ifstream> open_file(const std::string& filename)
{
	std::ifstream ifs {filename};
	if(!ifs.is_open())
		return err<std::ifstream>("Could not open file \"" + filename + "\"");
	return just(std::move(ifs));
}

expected<void> run(std::unique_ptr<pf_algorithm> algorithm)
{
	printer p {std::move(algorithm)};
	p.run();
	return true;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		print_usage(argv[0]);
		return 1;
	}
	auto r = open_file(argv[1])
			.and_then(maze::load_from_stream)
			.and_then(pick_algorithm, argv[2])
			.and_then(run);
	if(!r)
	{
		std::cout << "error: " << r.error() << std::endl;
		return 1;
	}
	return 0;
}
