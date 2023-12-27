#pragma once

#include <vector>
#include <variant>
#include <string>
#include <array>
#include <ranges>

#include <getopt.h>

#include "../utility/expected.hpp"
#include "../utility/utility.hpp"
#include "../utility/zip_view.hpp"
#include "opts_concepts.hpp"

using getopt_option = option;
/**
 * Structure holding a list of parsed options.
 * options -- list of options given as variant<AllOptions...>
 * nonpositional_arguments -- remaining nonpositoinal arguments given as strings
 */
template <option_like<getopt_option> ... Options>
struct options_impl
{
    using opt = std::variant<Options...>;
    std::vector<opt> options;
    std::vector<std::string> nonpositional_arguments;
};


namespace detail
{
    template <option_like <getopt_option> Option, option_like <getopt_option> ...AllOptions>
    requires (std::is_same_v<Option, AllOptions> || ...)
    
    struct expected_variant_lift
    {
        using opt = std::variant<AllOptions...>;
        
        static expected<opt> parse(const char* arg)
        {
            return Option::parse(arg).and_then(
                    [](const Option& optx) -> expected<opt>
                    {
                        return just(opt(optx));
                    });
        }
    };
}

template <help_like<getopt_option> Help, option_like<getopt_option> ... Options>
struct option_parser
{
    static std::variant<Help, expected<options_impl<Options...>>> parse(int argc, char* argv[])
    {
        static_assert(Help::opt_info.has_arg == no_argument, "Help option should not have an argument");
        static constexpr std::array long_opts = {
                Options::opt_info ...,
                Help::opt_info,
                option {0, 0, 0, 0}
        };
        static constexpr std::array parse_callbacks = {
                &detail::expected_variant_lift<Options, Options...>::parse...,
        };
        using result_type = options_impl<Options...>;
        result_type result;
        opterr = 0;
        optind = 1;
        while (true)
        {
            int c = getopt_long(argc, argv,
                                construct_shortopts(long_opts.data()).c_str(),
                                long_opts.data(),
                                nullptr);
            if (c == -1)
                break;
            switch (c)
            {
                case Help::opt_info.val:
                    return Help {};
                case '?':
                    return err<result_type>(fmt("unknown option %s", argv[optind - 1]));
                case ':':
                    return err<result_type>(fmt("missing argument to option %c", optopt));
                default:
                    for (auto [option, parse]: zip_view(long_opts, parse_callbacks))
                    {
                        if (option.val == c)
                        {
                            auto opt = parse(optarg);
                            if (!opt)
                                return err<result_type>(opt.error());
                            result.options.push_back(*opt);
                        }
                    }
            }
        }
        
        for (; optind < argc; ++optind)
            result.nonpositional_arguments.emplace_back(argv[optind]);
        return just(result);
    }
};