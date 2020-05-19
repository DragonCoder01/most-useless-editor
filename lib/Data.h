#pragma once

#include <vector>
#include <cinttypes>
#include <string>
#include <fstream>

struct Data {
private:
	void resize(size_t index) {
		if (index >= content.size()) {
			content.resize(index+1, 0);
		}
	}

public:
	std::vector<uint8_t> content;
	size_t offset = 0;

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

	void save(const std::string& filename) {
		std::ofstream file{filename};
		for (auto c : content) {
			file.put(c);
		}
		file.close();
	}

	void delete_last_bit() {
		if (offset!=0) {
			--offset;
			clearBit(offset);
			if (offset % 8 == 0){
				content.pop_back();
			}
		}
	}

	static Data load(const std::string& filename) {
		std::ifstream file{filename, std::ios::binary | std::ios::in};
		Data data;
		int index = 0;

		for (char c; file.get(c); ++index) {
			data.setByte(index, c);
		}

		data.offset = index*8;
		file.close();
		return data;
	}

};
