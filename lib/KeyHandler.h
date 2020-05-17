#pragma once

#include <functional>
#include <vector>

/**
 * This class executes some function when the corresponding keys are given to the `call` function.
 */
class KeyHandler {
	std::vector<int> keys;
	std::function<bool(int)> function;
public:
	explicit KeyHandler(std::function<bool(int)> f) : function(std::move(f)) { }
	explicit KeyHandler(int key, std::function<bool(int)> f) : function(std::move(f)) {
		keys.push_back(key);
	}
	explicit KeyHandler(const std::vector<int> &keys_, std::function<bool(int)> f) : function(std::move(f)) {
		for (auto k : keys_) {
			keys.push_back(k);
		}
	}

	/**
	 *
	 * @param k ... recently typed key
	 */
	bool call(int k) {
		for (auto key : keys) {
			if (k == key) {
				return function(k);
			}
		}
		return true;
	}
};