#pragma once

#include <chrono>

struct opt_sleep_time
{
    std::chrono::milliseconds duration;
    
    static expected<opt_sleep_time> parse(const char* arg)
    {
        using namespace std::string_literals;
        return parse_string<unsigned int>(arg, "could not parse_string milliseconds from \""s + arg + "\"")
                .and_then(
                        [&](unsigned int x)
                        {
                            return just(opt_sleep_time {std::chrono::milliseconds(x)});
                        });
    }
    static std::pair<std::string,std::string> help_message()
    {
        return {"-s|--sleep_time NUM","sets the delay on each operation"};
    }
    static constexpr struct option opt = {.name = "sleep_time", .has_arg = required_argument, .flag=nullptr, .val='s'};
};