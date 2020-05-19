#pragma once

#include "Editor.h"
#include "KeyHandler.h"
#include "util.h"
#include "Status.h"

#include <utility>
#include <vector>
#include <fstream>
#include <string>

class App {
public:
	Editor *edit;
	Status *top;
	Status *bottom;

	std::vector<KeyHandler> key_handlers;

	explicit App(std::vector<KeyHandler> kh) : key_handlers{std::move(kh)} {
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

	void start() {
		edit->load("output.bin");

		static int run = 0;
		if (run == 0) {
			run++;
			bool running = true;
			while (running) {
				int code = getch();

				for (auto k : key_handlers) {
					running = k.call(code);
					if (!running) break; // break out of the for loop, so the while loop can stop
				}
			}
		}
	}

	~App() {
		edit->save("output.bin");
		delete edit;
		delete top;
		delete bottom;
		endwin();
	}
};