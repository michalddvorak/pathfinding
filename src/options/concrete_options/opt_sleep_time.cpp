#include "opt_sleep_time.hpp"
#include "../opt_util.hpp"

expected<opt_sleep_time> opt_sleep_time::parse(const char* arg)
{
    using namespace std::string_literals;
    return parse_string<unsigned int>(arg, "could not parse_string milliseconds from \""s + arg + "\"")
            .and_then(
                    [&](unsigned int x)
                    {
                        return just(opt_sleep_time {std::chrono::milliseconds(x)});
                    });
}

std::pair<std::string, std::string> opt_sleep_time::help_message()
{
    return {construct_argument_help(opt, "NUM"), "sets the delay on each operation"};
}
