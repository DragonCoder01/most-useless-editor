#include <curses.h>
#include <vector>
#include <fstream>

#include "util.h"
#include "KeyHandler.h"
#include "Editor.h"

#include "App.h"

int main() {
	App app;

	int code = -1;
	bool running = true;

	std::vector<KeyHandler> keys{
		KeyHandler{{'0', '1'}, [&]() {
			app.edit->print_char(code);
		}},
		KeyHandler{{'q', 27}, [&](){
			running = false;
		}},
		KeyHandler{8, [&](){
			app.edit->backspace();
		}}
	};

	while (running) {
		code = getch();

		for (auto k : keys) {
			k.call(code);
		}
	}

	std::ofstream file{"output.bin"};
	for (auto c : app.edit->get_raw_data()) {
		file.put(c);
	}
	file.close();

	return 0;
}