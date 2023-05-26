#include "runner.hpp"

runner::runner(std::unique_ptr<pf_algorithm> algorithm, const maze& maze, const std::vector<opt>& options) : algorithm_ {std::move(algorithm)},
																											 maze_ {maze},
																											 printer_ {&maze_, algorithm_.get(), options} { }
