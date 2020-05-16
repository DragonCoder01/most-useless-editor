#pragma once

#include "Editor.h"
#include "KeyHandler.h"
#include "util.h"
#include "Status.h"

class App {
public:
	Editor *edit;
	Status *top;
	Status *bottom;
	App() {
		initscr(); // Initialises curses
		noecho();  // Don't echo out the typed character
		raw();     // Also pass things like CTRL+C etc. to the program
		keypad(stdscr, true); // Pass arrow keys, function keys etc. to the program
		refresh(); // This is necessary because otherwise the screen will behave strangely

		int width = 1+((COLS-2)/9)*9;
		int height = LINES;

		edit = new Editor{{0, 1}, {width, height-2}};
		top = new Status{{0, 0}, {width, 1}, "mu-edit"};
		bottom = new Status{{0, LINES-1}, {width, 1}, "Press `q` or `ESC` to exit..."};
	}

	~App() {
		delete edit;
		delete top;
		delete bottom;
		endwin();
	}
};