#pragma once

#include <curses.h>
#include <cstdint>
#include <vector>

#include "util.h"
#include "Data.h"

class Editor {
	vec2 cursor_position;
	vec2 position;
	vec2 dimensions{};

	Data data;
	size_t offset = 0;

	int columns;

	WINDOW *window;

	void output() {
		wclear(window);
		wmove(window, 0, 0);
		int spaces = 0;
		{
			int tmp = 0;
			bool break_out = false;
			if (offset != 0) {
				for (int i = 0; i < data.content.size(); ++i) {
					for (int j = 0; j < 8; ++j) {
						waddch(window, (data.content[i] & 1 << (7 - j)) ? '1' : '0');
						tmp++;
						if (tmp >= offset) {
							break_out = true;
							break;
						}
					}
					if ((i + 1)%(columns + 1)!=0) {
						waddch(window, ' ');
						++spaces;
					}
					if (break_out)
						break;
				}
			}
		}
		int pos_x = (position.x + (int)offset + spaces) % dimensions.x;
		int pos_y = (position.x + (int)offset + spaces) / dimensions.x;

		move(pos_y + 2, pos_x);

		wrefresh(window);
	}

public:
	Editor(vec2 position, vec2 dim) : position(position),
	                                  cursor_position{0, 0},
		                              dimensions{dim.x - 2, dim.y - 2} {
		columns = (dimensions.x/9);

		auto tmpwindow = newwin(dimensions.y + 2, dimensions.x + 2, position.y, position.x);
		box(tmpwindow, 0, 0);
		mvwprintw(tmpwindow, 0, 2, "|editor|");
		wrefresh(tmpwindow);
		window = newwin(dimensions.y, dimensions.x, position.y + 1, position.x + 1);
		wmove(window, 0, 0);
		wrefresh(window);
	}

	void print_char(int code) {
		if (code=='0') {
			data.clearBit(offset);
			++offset;
		} else if (code=='1') {
			data.setBit(offset);
			++offset;
		}

		output();
	}

	void backspace() {
		if (offset!=0) --offset;
		output();
	}
};