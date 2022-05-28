#include <iostream>
#include "observable.hpp"
#include "pf_algorithm.hpp"


class initial_printer : public observer<const maze&>
{
 public:
	void update(const maze& maze) override;
};

class updating_printer : public observer<algorithm_state, coord>
{
 public:
	void update(algorithm_state st, coord coord) override;
};