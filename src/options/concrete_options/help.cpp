#include "help.hpp"
#include "../opt_util.hpp"
std::pair <std::string, std::string> help::help_message()
{
    return {construct_argument_help(opt_info), "display this help message"};
}
