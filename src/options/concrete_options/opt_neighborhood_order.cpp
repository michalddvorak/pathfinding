#include "opt_neighborhood_order.hpp"
#include "../opt_util.hpp"

expected<opt_neighborhood_order> opt_neighborhood_order::parse(const char* arg)
{
    opt_neighborhood_order result;
    const std::map<char, std::function<coord(const coord&)>> fns =
            {
                    {'l', &coord::left},
                    {'r', &coord::right},
                    {'u', &coord::up},
                    {'d', &coord::down}
            };
    using namespace std::string_literals;
    return boolean_lift(is_same_up_to_permutation,
                        "invalid permutation \""s + arg + "\", it must be a permutation of \"lrud\"")(arg, "lrud")
            .and_then(
                    [&]()
                    {
                        opt_neighborhood_order result;
                        std::transform(arg, arg + strlen(arg), result.order.begin(),
                                       [&](char c) { return fns.at(c); });
                        return just(result);
                    });
}

std::pair<std::string, std::string> opt_neighborhood_order::help_message()
{
    return {construct_argument_help(opt_info, "PERM"),
            "PERM is a permutation of \"lrud\" and this modifies the order in which the neighborhood is traversed in all algorithms"};
}
