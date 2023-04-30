#pragma once
#include "pfalgorithm.hpp"

struct bfs : pf_algorithm
{
	using pf_algorithm::pf_algorithm;
	void run() override;
};