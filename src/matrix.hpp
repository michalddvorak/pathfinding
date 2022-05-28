#pragma once

#include <utility>
#include <algorithm>
#include <cstdint>

template<typename T>
class matrix
{
 public:
	matrix(size_t rows, size_t cols) : m_rows(rows),
									   m_cols(cols),
									   m_internal_array(init_array(rows, cols)) { }
	
	T* operator [](size_t i)
	{
		return m_internal_array[i];
	}
	const T* operator [](size_t i) const
	{
		return m_internal_array[i];
	}
	
	matrix(const matrix& other) : m_rows(other.m_rows),
								  m_cols(other.m_cols),
								  m_internal_array(init_array(other.m_rows, other.m_cols))
	{
		std::copy(*other.m_internal_array, *other.m_internal_array + m_rows * m_cols, *m_internal_array);
	}
	matrix(matrix&& other) noexcept: m_rows(other.m_rows),
									 m_cols(other.m_cols),
									 m_internal_array(std::exchange(other.m_internal_array, nullptr)) { }
	
	matrix& operator =(matrix other) noexcept
	{
		other.swap(*this);
		return *this;
	}
	~matrix()
	{
		if(m_internal_array != nullptr)
			delete[] *m_internal_array;
		delete[] m_internal_array;
	}
	template<typename X>
	friend void swap(matrix<X>& a, matrix<X>& b) noexcept;
	void swap(matrix& other) noexcept
	{
		std::swap(m_internal_array, other.m_internal_array);
		std::swap(m_rows, other.m_rows);
		std::swap(m_cols, other.m_cols);
	}
	
	size_t rows() const
	{
		return m_rows;
	}
	size_t cols() const
	{
		return m_cols;
	}
 private:
	static T** init_array(size_t rows, size_t cols)
	{
		T** internal_array = new T* [rows];
		T* actual_array = new T[rows * cols];
		for(size_t i = 0; i < rows; ++i)
			internal_array[i] = actual_array + i * cols;
		return internal_array;
	}
	size_t m_rows;
	size_t m_cols;
	T** m_internal_array;
};

template<typename T>
void swap(matrix<T>& a, matrix<T>& b) noexcept
{
	a.swap(b);
}





