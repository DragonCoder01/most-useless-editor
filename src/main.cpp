#include <iostream>
#include <istream>
#include <string>

#include <conio.h>

#define using_whitespace 1

void print_string(const std::string& data) {
	for (auto c : data) {
		uint8_t character = (uint8_t)c;
		for (int i = 0; i < 7; ++i) {
			std::cout << !!(character & (1<<i)); // I know you can print integers directly as binary, but this way is much worse (or the best way, if you usually work with a system that doesn't have the STL D: )
		}
		if constexpr (using_whitespace) {
			std::cout << " ";
		}
	}
}

int main(int argc, const char** argv) {
	print_string("Hello darkness my old friend.");
	std::cout << "\nHello darkness my old friend.";

	while (true) {
		static int counter = 0;
		char c = getch();
		++counter;

		if (counter > 8) {
			counter = 1;
			if constexpr (using_whitespace) {
				std::cout << " ";
			}
		}

		if (c == '0' || c == '1') {
			std::cout << c;
		} else if (c == 3) {
			break;
		} else if (c == 27) {
			std::cout << "\nEntered ESC mode\n";
		} else {
			std::cout << '\7';
			std::cout << '\n' << (int)(c);
		}
	}
}