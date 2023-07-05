#pragma once

#include <array>
#include <termios.h>
#include "../coord.hpp"
#include "../utility/fwd.hpp"

struct rgb
{
	uint8_t r, g, b;
};

class graphics
{
 public:
	virtual ~graphics() = default;
	virtual void print(const coord& pos, const std::string& str) = 0;
	virtual void clear() = 0;
	virtual void set_cursor(const coord& pos) = 0;
	void print_all(const coord& pos, auto&& ... args)
	{
		std::stringstream ss;
		(ss << ... << FWD(args));
		return print(pos, ss.str());
	}
	virtual void print_with_fg_color(const coord& pos, const std::string& what, rgb color) = 0;
	virtual void print_with_bg_color(const coord& pos, const std::string& what, rgb color) = 0;
	virtual void print_with_blink(const coord& pos, const std::string& what, rgb color) = 0;
};


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
	
	static constexpr auto with_fg_color(int r, int g, int b)
	{
		return [=](const std::string& what) {
			return color_fg(r, g, b) + what + ATTR_END;
		};
	}
	
	static constexpr auto with_bg_color(int r, int g, int b)
	{
		return [=](const std::string& what) {
			return color_bg(r, g, b) + what + ATTR_END;
		};
	}
	static constexpr auto with_blink()
	{
		return [&](const std::string& what) { return BLINK + what + ATTR_END; };
	}
 private:
	
	static std::string color_bg(int r, int g, int b);
	static std::string color_fg(int r, int g, int b);
	void hide_cursor();
	void init_terminal();
	void restore_terminal();
	void show_cursor();
	struct termios old_ttystate_;
	
	static constexpr const char* ATTR_END = "\033[0m";
	static constexpr const char* BLINK = "\033[5m";
};