#pragma once

#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ranges>
#include <cstdarg>
#include "limits.h"
#include "expected.hpp"
#include "overload.hpp"


/**
 * @brief Function determines whether two strings are same up to permutation of the individual symbols
 * @param a first string
 * @param b second string
 * @return true if the strings are same up to permutation of their symbols
 */
inline bool is_same_up_to_permutation(const std::string& a, const std::string& b)
{
	if(a.size() != b.size())
		return false;
	std::string a_ = a;
	std::string b_ = b;
	std::sort(a_.begin(), a_.end());
	std::sort(b_.begin(), b_.end());
	return a_ == b_;
}

/**
 * @brief Functiondetermines whether two strings are equal case insensitive
 * @param a first string
 * @param b second string
 * @return true if yes, false if no
 */
inline bool equals_insensitive(const std::string& a, const std::string& b)
{
	return strcasecmp(a.c_str(), b.c_str()) == 0;
}

/**
 * @brief Functions opens file identified by its filename
 * @param filename name of the file
 * @return expected containing ifstream on success, expected containing an error otherwise
 */
inline expected<std::ifstream> open_file(const std::string& filename)
{
	std::ifstream ifs {filename};
	if(!ifs.is_open())
		return err<std::ifstream>("Could not open file \"" + filename + "\"");
	return just(std::move(ifs));
}

/**
 * @brief Extract a variable of type T from a string
 */
template<typename T, typename Err=std::string>
expected<T, Err> parse_string(const std::string& arg, const Err& error_message = Err())
{
	std::stringstream ss {arg};
	T result;
	if(!(ss >> result))
		return err<T, Err>(error_message);
	return just<Err>(result);
}

inline void visit_each(std::ranges::range auto&& range, auto&& ... overloads)
{
	for(auto&& var: range)
		std::visit(overload {FWD(overloads)...}, var);
}
/**
 * Formats the given string simillarly to sprintf, but returns
 * std::string with the result
 */
inline std::string fmt(const char *format, ...) {
    va_list args1;
    va_list args2;
    va_start(args1, format);
    va_copy(args2, args1);
    
    std::string buf(vsnprintf(nullptr, 0, format, args1), '\0');
    va_end(args1);
    
    vsnprintf(buf.data(), buf.size() + 1, format, args2);
    va_end(args2);
    
    return buf;
}

