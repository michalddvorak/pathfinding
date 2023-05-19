#pragma once

#include "pfalgorithm.hpp"

class bfs : public pf_algorithm
{
	void run(const maze& maze) override;
};