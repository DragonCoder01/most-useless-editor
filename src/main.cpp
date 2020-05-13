#include <curses.h>

int main() {
	initscr(); // Initialises curses
	noecho();  // Don't echo out the typed character
	raw();     // Also pass things like CTRL+C etc. to the program
	keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program

	auto* editor = newwin(LINES-2, COLS, 1, 0);
	auto* top = newwin(1, COLS, 0, 0);

	box(editor, 0, 0);
	mvwprintw(editor, 0, 2, "|editor|");
	wrefresh(editor);
	
	int code = -1;
	while (code != 'q') {
		code = getch();
		if (code == '0' || code == '1') {
			mvwaddch(editor, 1, 1, code);
			move(2, 1);
			x+=1;
		}
		
		refresh();
		wrefresh(editor);

	}
	
	endwin();

	return 0;
}