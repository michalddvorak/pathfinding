#pragma once
#include <vector>
#include "coord.hpp"


template<typename T>
class matrix
{
 public:
	matrix(size_t rows, size_t cols, const T& value = T()) : rows_ {rows},
															 cols_ {cols},
															 array_(rows_, std::vector<T>(cols_, value)) { }
	const std::vector<T>& operator [](size_t i) const
	{
		return array_[i];
	}
	std::vector<T>& operator [](size_t i)
	{
		return array_[i];
	}
	bool valid(const coord& pos) const
	{
		return pos.i < rows_ && pos.j < cols_;
	}
	const T& operator ()(const coord& pos) const
	{
		return (*this)(pos.i, pos.j);
	}
	T& operator ()(const coord& pos)
	{
		return (*this)(pos.i, pos.j);
	}
	const T& operator ()(size_t i, size_t j) const
	{
		return array_[i][j];
	}
	T& operator ()(size_t i, size_t j)
	{
		return array_[i][j];
	}
	size_t rows() const
	{
		return rows_;
	}
	size_t cols() const
	{
		return cols_;
	}
 
 private:
	size_t rows_;
	size_t cols_;
	std::vector<std::vector<T>> array_;
};
