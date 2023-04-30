#include "pfalgorithm.hpp"

pf_algorithm::pf_algorithm(maze&& maze) : maze_ {std::move(maze)} { }
const maze& pf_algorithm::get_maze() const
{
	return maze_;
}
void pf_algorithm::reconstruct_path(const matrix<coord>& prev)
{
	auto cur = maze_.end;
	on_step();
	on_path(cur);
	while(true)
	{
		if(cur == maze_.start)
			break;
		cur = prev(cur);
		on_step();
		on_path(cur);
	}
}
