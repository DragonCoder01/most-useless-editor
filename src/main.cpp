#include "KeyHandler.h"

#include "App.h"

int main() {
	App app{{
		KeyHandler{{'0', '1'}, [&](int code) {
			app.edit->print_char(code);
			return true;
		}},
		KeyHandler{{'q', 27}, [&](int) {
			return false;
		}},
		KeyHandler{8, [&](int) {
			app.edit->backspace();
			return true;
		}}
    }};

	app.start();

	return 0;
}