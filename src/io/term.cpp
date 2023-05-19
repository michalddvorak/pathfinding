#include <iostream>
#include <sstream>
#include <unistd.h>
#include "term.hpp"

void term::hide_cursor()
{
	std::cout << "\033[?25l";
}
void term::init_terminal()
{
	tcgetattr(STDIN_FILENO, &old_ttystate_); //store old ttystate
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~ICANON; //disable canonical mode
	ttystate.c_cc[VMIN] = 1; //react on 1 character
	ttystate.c_lflag &= ~ECHO; //don't echo pressed characters
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
void term::restore_terminal()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &old_ttystate_);
}
void term::show_cursor()
{
	std::cout << "\033[?25h";
}
std::string term::color_bg(int r, int g, int b)
{
	std::stringstream ss;
	ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
	std::string res;
	ss >> res;
	return res;
}
std::string term::color_fg(int r, int g, int b)
{
	std::stringstream ss;
	ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	std::string res;
	ss >> res;
	return res;
}
void term::clear()
{
	std::cout << "\033[2J";
}
void term::set_cursor(const coord& p) {
	std::cout << "\033[" << p.i + 1 << ';' << p.j + 1 << 'H';
}
term::~term() {
	restore_terminal();
	show_cursor();
}
term::term() {
	hide_cursor();
	init_terminal();
}
std::string term::with_color(int r, int g, int b, const std::string& what)
{
	return color_fg(r, g, b) + what + ATTR_END;
}
std::string term::with_blink(const std::string& what)
{
	return BLINK + what + ATTR_END;
}
