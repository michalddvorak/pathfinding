#pragma once

#include <array>
#include <termios.h>
#include "../coord.hpp"
#include "../utility/fwd.hpp"
#include "../utility/rgb.hpp"

struct term
{
	term();
	~term();
	term(const term&) = delete;
	term(term&&) = delete;
	void operator =(const term&) = delete;
	term& operator =(term&&) = delete;
	static void set_cursor(const coord& p);
	template<typename ...Args>
	static void print(const coord& p, Args&& ... args)
	{
		set_cursor(p);
		(std::cout << ... << args).flush();
	}
	static void clear();
 
	static constexpr auto with_fg_color(rgb color)
	{
		return [=](const std::string& what) {
			return color_fg(color) + what + ATTR_END;
		};
	}
	
	static constexpr auto with_bg_color(rgb color)
	{
		return [=](const std::string& what) {
			return color_bg(color) + what + ATTR_END;
		};
	}
	static constexpr auto with_blink()
	{
		return [&](const std::string& what) { return BLINK + what + ATTR_END; };
	}
 private:
	
	static std::string color_bg(rgb color);
	static std::string color_fg(rgb color);
	void hide_cursor();
	void init_terminal();
	void restore_terminal();
	void show_cursor();
	struct termios old_ttystate_;
	
	static constexpr const char* ATTR_END = "\033[0m";
	static constexpr const char* BLINK = "\033[5m";
};