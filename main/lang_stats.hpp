#pragma once

#include <unordered_map>
#include <string>

struct LangStats {
	unsigned int size = 0;
	std::size_t files = 0;
	std::unordered_map<std::string, std::size_t> extentions;

	bool operator<(const LangStats& oth) const {
		return size < oth.size;
	}
};