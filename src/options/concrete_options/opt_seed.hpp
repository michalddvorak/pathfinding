#pragma once
#include <getopt.h>
#include "../../utility/expected.hpp"
#include "../../utility/utility.hpp"


struct opt_seed
{
    unsigned long seed;
    
    static expected<opt_seed> parse(const char* arg);
    
    static std::pair<std::string, std::string> help_message();
    
    static constexpr struct option opt_info = {.name = "seed", .has_arg = required_argument, .flag=nullptr, .val='d'};
};