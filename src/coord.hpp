#pragma once
#include <cstddef>

struct coord
{
	size_t i, j;
	coord down() const;
	coord up() const;
	coord left() const;
	coord right() const;
};

bool operator ==(const coord& a, const coord& b);
bool operator !=(const coord& a, const coord& b);
