#pragma once

#include <termios.h>
#include "../coord.hpp"

struct term
{
	term();
	~term();
	term(const term&) = delete;
	term(term&&) = default;
	void operator=(const term&) = delete;
	term& operator=(term&&) = default;
	static void set_cursor(const coord& p);
	template<typename ...Args>
	static void print(const coord& p, Args&& ... args)
	{
		set_cursor(p);
		(std::cout << ... << args).flush();
	}
	static std::string color_bg(int r, int g, int b);
	
	static std::string color_fg(int r, int g, int b);
	static void clear();
	
	static std::string with_color(int r, int g, int b, const std::string& what);
	static std::string with_blink(const std::string& what);
 private:
	void hide_cursor();
	void init_terminal();
	void restore_terminal();
	void show_cursor();
	struct termios old_ttystate_;
	
	static constexpr const char* ATTR_END = "\033[0m";
	static constexpr const char* BLINK = "\033[5m";
};