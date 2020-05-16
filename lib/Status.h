#pragma once

#include "util.h"
#include <string>

class Status {
	vec2 position, dimensions;
	WINDOW *window;
public:
	Status(vec2 pos, vec2 dim, const std::string& message = "") : position{pos}, dimensions{dim} {
		window = newwin(dim.y, dim.x, pos.y, pos.x);
		wprintw(window, "%s", message.c_str());
		wrefresh(window);
	}

	void update_message(const std::string& message) {
		wclear(window);
		wprintw(window, "%s", message.c_str());
		wrefresh(window);
	}
};