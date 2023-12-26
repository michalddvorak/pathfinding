#include "coord.hpp"

coord coord::down() const
{
	return {i + 1, j}; //(0,0) is upper left corner
}
coord coord::up() const
{
	return {i - 1, j};
}
coord coord::left() const
{
	return {i, j - 1};
}
coord coord::right() const
{
	return {i, j + 1};
}
bool operator ==(const coord& a, const coord& b)
{
	return a.i == b.i && a.j == b.j;
}
bool operator !=(const coord& a, const coord& b)
{
	return !(a == b);
}
