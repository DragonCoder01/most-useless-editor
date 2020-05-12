#include <curses.h>

int main() {
	initscr(); // Initialises curses
	noecho();  // Don't echo out the typed character
	raw();     // Also pass things like CTRL+C etc. to the program
	keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program

	printw("Hello World!");
	refresh();
	
	int code = -1;
	while (code != 'q') {
		code = getch();
		if (code == '0' || code == '1') {
			addch(code);
		}
		refresh();
	}
	
	endwin();

	return 0;
}