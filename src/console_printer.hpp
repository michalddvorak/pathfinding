#include <iostream>
#include "observable.hpp"
#include "pf_algorithm.hpp"


class console_printer : public observer<size_t, size_t>
{
 public:
	void update(const size_t&, const size_t&) override;
};