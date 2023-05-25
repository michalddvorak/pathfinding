#pragma once

#include <string>
#include <algorithm>

/**
 * @brief Function determines whether two strings are same up to permutation of the individual symbols
 */
inline bool is_same_up_to_permutation(std::string a, std::string b)
{
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	return a == b;
}