#pragma once

#include "../utility/type_list.hpp"
#include "opt_util.hpp"
#include "concrete_options/opt_neighborhood_order.hpp"
#include "concrete_options/opt_sleep_time.hpp"
#include "concrete_options/opt_seed.hpp"
#include "concrete_options/help.hpp"
#include "opts_impl.hpp"


using all_options = type_list<opt_neighborhood_order, opt_sleep_time, opt_seed>;
using extended_options = all_options::push_front<help>;
using options = all_options::apply<options_impl>;
using opt = options::opt;

std::variant<help, expected<options>> parse_options(int argc, char* argv[]);
