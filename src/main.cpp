#include <iostream>
#include <string>

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

int main() {
	print_string("Hello darkness my old friend.");
	std::cout << "Hello darkness my old friend.";
}