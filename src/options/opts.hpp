#pragma once

#include <vector>
#include <variant>
#include <getopt.h>
#include "../utility/expected.hpp"
#include "../utility/utility.hpp"
#include "../utility/type_list.hpp"
#include "opt_util.hpp"
#include "opt_neighborhood_order.hpp"
#include "opt_sleep_time.hpp"
#include "opt_seed.hpp"

struct help_tag { };

using all_options = type_list<opt_neighborhood_order, opt_sleep_time, opt_seed>;

using opt = all_options::apply<std::variant>;

template <typename ... Options>
struct options_impl
{
    std::vector<opt> options;
    std::vector<std::string> nonpositional_arguments;
};

using options = all_options::apply<options_impl>;

namespace detail
{
    template <typename Option>
    struct lift_parse_helper
    {
        static expected<opt> parse(const char* arg)
        {
            return Option::parse(arg).and_then(
                    [&](const Option& optx) -> expected<opt>
                    {
                        return just(opt(optx));
                    });
        }
    };
}

template <typename ... Options>
struct option_parser
{
    static std::variant<help_tag, expected<options_impl<Options...>>> parse(int argc, char* argv[])
    {
        using result_type = options_impl<Options...>;
        static constexpr struct option long_opts[] = {
                Options::opt ...,
                {.name = "help", .has_arg = no_argument, .flag = nullptr, .val = 'h'},
                {0, 0, 0, 0}
        };
        static constexpr std::array callbacks = {
                &detail::lift_parse_helper<Options>::parse...,
        };
        
        result_type result;
        using namespace std::string_literals;
        int c;
        opterr = 0;
        optind = 1;
        while ((c = getopt_long(argc, argv, construct_shortopts(long_opts).c_str(), long_opts, nullptr)) != -1)
        {
            for (size_t i = 0; i < sizeof... (Options); ++i)
                if (long_opts[i].val == c)
                {
                    auto option = callbacks[i](optarg);
                    if (!option)
                        return err<result_type>(option.error());
                    result.options.push_back(*option);
                    break;
                }
            switch (c)
            {
                case 'h':
                    return help_tag {};
                case '?':
                    return err<result_type>("unknown option "s + argv[optind - 1]);
                case ':':
                    return err<result_type>("missing argument to option "s + (char) optopt);
            }
        }
        
        for (; optind < argc; ++optind)
            result.nonpositional_arguments.emplace_back(argv[optind]);
        return just(result);
    }
};

inline std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[])
{
    return all_options::apply<option_parser>::parse(argc, argv);
}

