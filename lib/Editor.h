#pragma once

#include <curses.h>
#include <cstdint>
#include <vector>

#include "util.h"

class Editor {
	vec2 cursor_position;
	vec2 position;
	vec2 dimensions;

	std::vector<uint8_t> content;

	WINDOW* window;

	int space = 0;
	uint8_t byte = 0;

	void next_cursor_position() {
		++cursor_position.x;

		if (cursor_position.x > dimensions.x - 3) {
			cursor_position.x = 0;
			++cursor_position.y;
			if (cursor_position.y > dimensions.y - 3) {
				cursor_position.y = 0;
			}
		}
		move(position.y + 1 + cursor_position.y, position.x + 1 + cursor_position.x);
	}

	void prev_cursor_position() {
		--cursor_position.x;

		if (cursor_position.x < 0) {
			cursor_position.x = dimensions.x - 3;
			--cursor_position.y;
			if (cursor_position.y < 0){
				cursor_position.y = 0;
				cursor_position.x = 0;
			}
		}
		move(position.y + 1 + cursor_position.y, position.x + 1 + cursor_position.x);
	}

public:
	Editor(vec2 position, vec2 dimensions) : position(position), dimensions(dimensions), cursor_position{0, 0} {
		window = newwin(dimensions.y, dimensions.x, position.y, position.x);
		box(window, 0, 0);
		mvwprintw(window, 0, 2, "|editor|");
		move(position.y + 1, position.x + 1);
		wrefresh(window);
	}

	void print_char(int code) {
		mvwaddch(window, 1 + cursor_position.y, 1 + cursor_position.x, code);
		next_cursor_position();
		++space;
		byte <<= 1;
		if (code == '0' || code == '1')
			byte |= code - '0';
		if (space >= 8) {
			content.push_back(byte);
			byte = 0;
			space = 0;
			mvwaddch(window, 1 + cursor_position.y, 1 + cursor_position.x, ' ');
			next_cursor_position();
			if (cursor_position.x == 1) { // FIXME: sucha hax
				cursor_position.x--;
				move(position.y + 1 + cursor_position.y, position.x + 1 + cursor_position.x);
			}
		}
		wrefresh(window);
	}

	void backspace() {
		space--;
		if (space < 0) {
			space = 7;
			if (!content.empty()) {
				byte = content.back();
				content.pop_back();
			} else {
				space = 0;
			}
		}
		byte >>= 1;
		prev_cursor_position();
		--space;
		print_char(' ');
		byte >>= 1;
		prev_cursor_position();
	}
};