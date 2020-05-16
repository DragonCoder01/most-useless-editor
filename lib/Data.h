#pragma once

#include <vector>
#include <cinttypes>

struct Data {
private:
	void resize(size_t index) {
		if (index >= content.size()) {
			content.resize(index+1, 0);
		}
	}

public:
	std::vector<uint8_t> content;

	uint8_t getByte(size_t index) {
		if (index < 0) index = 0;
		resize(index);
		return content[index];
	}

	bool getBit(size_t index) {
		if (index < 0) index = 0;
		resize(((index+8)/8) - 1);
		return (content[index/8] & (1 << (7-index%8)))!=0;
	}

	void setBit(size_t index) {
		if (index < 0) index = 0;
		resize(((index+8)/8) - 1);
		content[index/8] |= (1<<(7-index%8));
	}

	void clearBit(size_t index) {
		if (index < 0) index = 0;
		resize(((index+8)/8) - 1);
		content[index/8] &= ~(1<<(7-index%8));
	}

	void setByte(size_t index, uint8_t data) {
		if (index < 0) index = 0;
		resize(index);
		content[index] = data;
	}

	void removeByte(size_t index) {
		if (index < 0) index = 0;
		resize(index);
		content.erase(content.begin() + index);
	}

	[[nodiscard]] size_t size() const {
		return content.size()*8;
	}
};