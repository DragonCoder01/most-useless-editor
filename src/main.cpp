#include <curses.h>
#include <vector>

#include "util.h"
#include "KeyHandler.h"
#include "Editor.h"

int main() {
	initscr(); // Initialises curses
	noecho();  // Don't echo out the typed character
	raw();     // Also pass things like CTRL+C etc. to the program
	keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program
	refresh(); // This is necessary because otherwise the screen will behave strangely


	WINDOW *top = newwin(1, COLS, 0, 0);
	mvwprintw(top, 0, 0, "mu-edit %d", COLS);
	wrefresh(top);
	Editor edit{{0, 1}, {1+((COLS-2)/9)*9, LINES-2}};

	int code = -1;
	bool running = true;

	std::vector<KeyHandler> keys{
		KeyHandler{{'0', '1'}, [&]() {
			edit.print_char(code);
		}},
		KeyHandler{{'q', 27}, [&](){
			running = false;
		}},
		KeyHandler{8, [&](){
			mvwprintw(top, 0, 0, "mu-edit %s", "meh");
			wrefresh(top);
			edit.backspace();
		}}
	};

	while (running) {
		code = getch();
		mvwprintw(top, 0, 0, "mu-edit %d    ", code);
		wrefresh(top);

		for (auto k : keys) {
			k.call(code);
		}
	}

	endwin();

//	std::ofstream file{"output.bin"};
//	for (auto c : content) {
//		file.put(c);
//	}
//	file.close();

	return 0;
}