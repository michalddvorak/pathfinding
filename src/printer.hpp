#include <iostream>
#include "observable.hpp"
#include "pf_algorithm.hpp"


class printer : public observer<const maze&>, public observer<algorithm_state, coord, const maze&>
{
 public:
	void on_event(const maze& maze) override;
	void on_event(algorithm_state st, coord coord, const maze& maze) override;
};
