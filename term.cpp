#include <iostream>
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
