#pragma once

#include <string>
#include <map>
#include "../utility/expected.hpp"
#include "../coord.hpp"

struct opt_neighborhood_order
{
    std::array<std::function<coord(const coord&)>, 4> order = {&coord::left, &coord::down, &coord::right, &coord::up};
    
    static expected<opt_neighborhood_order> parse(const char* arg)
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
    
    static std::pair<std::string,std::string> help_message()
    {
        return {"-n|--neighborhood S","S is a permutation of \"lrud\" and this modifies the order in which the neighborhood is traversed in all algorithms"};
    }
    
    static constexpr struct option opt = {.name = "neighborhood", .has_arg = required_argument, .flag=nullptr, .val = 'n'};
};
