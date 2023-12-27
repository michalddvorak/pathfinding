#include "opt_seed.hpp"
#include "../opt_util.hpp"

expected<opt_seed> opt_seed::parse(const char* arg)
{
    using namespace std::string_literals;
    return parse_string<unsigned long>(arg, "could not seed from \""s + arg + "\"")
            .and_then(
                    [&](unsigned long x)
                    {
                        return just(opt_seed {x});
                    });
}

std::pair<std::string, std::string> opt_seed::help_message()
{
    return {construct_argument_help(opt, "NUM"), "seeds the random number generator"};
}
