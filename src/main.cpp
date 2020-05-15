#include <curses.h>
#include <cstdint>
#include <utility>
#include <vector>
#include <array>
#include <fstream>
#include <functional>

static std::vector<uint8_t> content;

struct vec2 {
	int x, y;
};

/**
 * This class executes some function when the corresponding keys are given to the `call` function.
 */
class KeyHandler {
	std::vector<uint8_t> keys;
	std::function<void()> function;
public:
	explicit KeyHandler(std::function<void()> f) : function(std::move(f)) { }
	explicit KeyHandler(uint8_t k, std::function<void()> f) : function(std::move(f)) {
		keys.push_back(k);
	}
	explicit KeyHandler(const std::vector<uint8_t> &keys_, std::function<void()> f) : function(std::move(f)) {
		for (auto k : keys_) {
			keys.push_back(k);
		}
	}

	/**
	 *
	 * @param k ... recently typed key
	 */
	void call(uint8_t k) {
		for (auto key : keys) {
			if (k == key) {
				function();
			}
		}
	}
};

class Editor {
	vec2 cursor_position;
	vec2 position;
	vec2 dimensions;

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
};

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
		}}
	};

	while (running) {
		code = getch();

		for (auto k : keys) {
			k.call(code);
		}
	}

	endwin();

	std::ofstream file{"output.txt"};
	for (auto c : content) {
		file.put(c);
	}
	file.close();

	return 0;
}