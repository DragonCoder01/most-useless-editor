#include <curses.h>
#include <cstdint>
#include <vector>
#include <fstream>

int main() {
	initscr(); // Initialises curses
	noecho();  // Don't echo out the typed character
	raw();     // Also pass things like CTRL+C etc. to the program
	keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program
	refresh();

	WINDOW* editor = newwin(LINES-2, COLS, 1, 0);
	WINDOW* top = newwin(1, COLS, 0, 0);
	mvwprintw(top, 0,0, "mu-edit");
	wrefresh(top);

	box(editor, 0, 0);
	mvwprintw(editor, 0, 2, "|editor|");
	wrefresh(editor);
	
	int code = -1;
	int x = 0, y = 0;
	int space = 0;
	uint8_t byte = 0;

	move(2 + y, 1 + x);

	std::vector<uint8_t> content;
	bool running = true;
	while (running) {
		code = getch();
		if (code == '0' || code == '1') {
			mvwaddch(editor, 1 + y, 1 + x, code);
			byte <<= 1;
			byte |= code - '0';
			++space;
			if (space >= 8) {
				content.push_back(byte);
				byte = 0;
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
		} else if (code == 'q' || code == 27) {
			running = false;
		}

		wrefresh(editor);
	}

	endwin();

	std::ofstream file{"output.txt"};
	for (auto c : content) {
		file.put(c);
	}
	file.close();

	return 0;
}