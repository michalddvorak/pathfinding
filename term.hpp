#include <termios.h>

struct term
{
	term()
	{
		hide_cursor();
		init_terminal();
	}
	~term()
	{
		restore_terminal();
		show_cursor();
	}
 private:
	void hide_cursor();
	void init_terminal();
	void restore_terminal();
	void show_cursor();
	struct termios old_ttystate_;
};