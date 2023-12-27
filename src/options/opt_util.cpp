#include "opt_util.hpp"
#include "../utility/utility.hpp"

std::string construct_shortopts(const struct option* long_opts)
{
    //: as a first character of optstring assures that ':' is returned if argument of an option is missing
    std::string res = ":";
    for (const struct option* o = long_opts; o->name != nullptr; ++o)
    {
        res += o->val;
        if (o->has_arg == required_argument)
            res += ":";
    }
    return res;
}

std::string construct_argument_help(const struct option& opt, const std::string& arg_name)
{
    return fmt("-%c|--%s%s",
               opt.val,
               opt.name,
               opt.has_arg == required_argument ? fmt(" %s", arg_name.c_str()).c_str() : "");
}