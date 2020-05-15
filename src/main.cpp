#include <curses.h>

int main() {
	initscr(); // Initialises curses
	noecho();  // Don't echo out the typed character
	raw();     // Also pass things like CTRL+C etc. to the program
	keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program

	WINDOW* editor = newwin(LINES-2, COLS, 1, 0);
//	auto* top = newwin(1, COLS, 0, 0);
//	mvwprintw(editor, 0, 2, "|editor|");
	wrefresh(editor);

	printw("mu-edit");
	refresh();


	box(editor, 0, 0);
	mvwprintw(editor, 0, 2, "|editor|");
	wrefresh(editor);
	
	int code = -1;
	int x = 0, y = 0;
	int space = 0;
	while (code != 'q') {
		code = getch();
		if (code == '0' || code == '1') {
			mvwaddch(editor, 1 + y, 1 + x, code);
			++space;
			if (space >= 8) {
				space = 0;
				waddch(editor, ' ');
				++x;
			}
			++x;
			if (x > COLS-3) {
				x = 0;
				++y;
				if (y > LINES - 5) {
					y = 0;
				}
			}
			move(2 + y, 1 + x);
		}

		wrefresh(editor);
	}

	endwin();

	return 0;
}