#pragma once

#include <utility>
#include <string>
#include <getopt.h>

struct help
{
    static std::pair<std::string, std::string> help_message();
    
    static constexpr struct option opt = {.name = "help", .has_arg = no_argument, .flag = nullptr, .val = 'h'};
};
