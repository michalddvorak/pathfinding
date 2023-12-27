#pragma once

#include <chrono>
#include <getopt.h>
#include "../utility/expected.hpp"
#include "../utility/utility.hpp"

struct opt_sleep_time
{
    std::chrono::milliseconds duration;
    
    static expected<opt_sleep_time> parse(const char* arg);
    static std::pair<std::string,std::string> help_message();
    static constexpr struct option opt = {.name = "sleep_time", .has_arg = required_argument, .flag=nullptr, .val='s'};
};