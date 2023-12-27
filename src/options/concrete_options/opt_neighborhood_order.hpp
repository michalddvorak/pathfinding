#pragma once

#include <string>
#include <map>
#include <getopt.h>
#include "../../utility/utility.hpp"
#include "../../utility/expected.hpp"
#include "../../coord.hpp"

struct opt_neighborhood_order
{
    std::array<std::function<coord(const coord&)>, 4> order = {&coord::left, &coord::down, &coord::right, &coord::up};
    
    static expected<opt_neighborhood_order> parse(const char* arg);
    
    static std::pair<std::string, std::string> help_message();
    
    static constexpr struct option opt_info = {.name = "neighborhood", .has_arg = required_argument, .flag=nullptr, .val = 'n'};
};
