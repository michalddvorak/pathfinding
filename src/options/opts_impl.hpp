#pragma once

#include <vector>
#include <variant>
#include <string>
#include <array>

#include <getopt.h>

#include "../utility/expected.hpp"
#include "../utility/utility.hpp"


using getopt_option = option;

template <typename T>
concept parseable =
requires(const char* arg)
{
    { T::parse(arg) } -> std::same_as<expected<T>>;
};

template <typename T>
concept has_opt =
requires
{
    { T::opt } -> std::convertible_to<getopt_option>;
};

template <typename T>
concept option_like = parseable<T> &&
                      has_opt<T> &&
                      requires
                      {
                          { T::help_message() } -> std::same_as<std::pair<std::string, std::string>>;
                      };

template <typename T>
concept help_like = has_opt<T>;

template <option_like ... Options>
struct options_impl
{
    using opt = std::variant<Options...>;
    std::vector<opt> options;
    std::vector<std::string> nonpositional_arguments;
};
/**
 * Structure holding a list of parsed options.
 * options -- list of options given as variant<Options...>
 * nonpositional_arguments -- remaining nonpositoinal arguments given as strings
 */

namespace detail
{
    template <option_like Option, option_like ...Options> requires (std::is_same_v<Option, Options> || ...)
    
    struct expected_variant_lift
    {
        using opt = std::variant<Options...>;
        
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

template <help_like Help, option_like ... Options>
struct option_parser
{
    static std::variant<Help, expected<options_impl<Options...>>> parse(int argc, char* argv[])
    {
        static_assert(Help::opt.has_arg == no_argument, "Help option should not have an argument");
        static constexpr std::array long_opts = {
                Options::opt ...,
                Help::opt,
                option {0, 0, 0, 0}
        };
        static constexpr std::array callbacks = {
                &detail::expected_variant_lift<Options, Options...>::parse...,
        };
        
        using result_type = options_impl<Options...>;
        result_type result;
        opterr = 0;
        optind = 1;
        while (true)
        {
            int c = getopt_long(argc, argv, construct_shortopts(long_opts.data()).c_str(), long_opts.data(), nullptr);
            if (c == -1)
                break;
            switch (c)
            {
                case Help::opt.val:
                    return Help {};
                case '?':
                    return err<result_type>(fmt("unknown option %s", argv[optind - 1]));
                case ':':
                    return err<result_type>(fmt("missing argument to option %c", optopt));
            }
            //std::views::zip would be nice here
            for (size_t i = 0; i < sizeof... (Options); ++i)
                if (long_opts[i].val == c)
                {
                    auto option = callbacks[i](optarg);
                    if (!option)
                        return err<result_type>(option.error());
                    result.options.push_back(*option);
                    break;
                }
            
        }
        
        for (; optind < argc; ++optind)
            result.nonpositional_arguments.emplace_back(argv[optind]);
        return just(result);
    }
};