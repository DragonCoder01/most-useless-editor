#pragma once

#include <functional>
#include <vector>

/**
 * This class executes some function when the corresponding keys are given to the `call` function.
 */
class KeyHandler {
	std::vector<int> keys;
	std::function<void()> function;
public:
	explicit KeyHandler(std::function<void()> f) : function(std::move(f)) { }
	explicit KeyHandler(int k, std::function<void()> f) : function(std::move(f)) {
		keys.push_back(k);
	}
	explicit KeyHandler(const std::vector<int> &keys_, std::function<void()> f) : function(std::move(f)) {
		for (auto k : keys_) {
			keys.push_back(k);
		}
	}

	/**
	 *
	 * @param k ... recently typed key
	 */
	void call(int k) {
		for (auto key : keys) {
			if (k == key) {
				function();
			}
		}
	}
};