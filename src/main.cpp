
#include <sstream>
#include <array>
#include <iomanip>


#include "utility/expected.hpp"
#include "algorithms/bfs.hpp"
#include "algorithms/dfs.hpp"
#include "options/opts.hpp"
#include "runner.hpp"
#include "algorithms/rands.hpp"
#include "algorithms/astar.hpp"
#include "algorithms/greedy.hpp"


expected<std::unique_ptr<pf_algorithm>> pick_algorithm(const std::string& name, const std::vector<opt>& options)
{
    using namespace std::string_literals;
    
    if (equals_insensitive(name, "bfs"))
        return just(pf_algorithm::make<bfs>(options));
    else if (equals_insensitive(name, "dfs"))
        return just(pf_algorithm::make<dfs>(options));
    else if (equals_insensitive(name, "random"))
        return just(pf_algorithm::make<rands>(options));
    else if (equals_insensitive(name, "astar"))
        return just(pf_algorithm::make<astar>(options));
    else if (equals_insensitive(name, "greedy"))
        return just(pf_algorithm::make<greedy>(options));
    return err<std::unique_ptr<pf_algorithm>>("unknown algorithm \""s + name + "\"");
}

namespace detail
{
    template <has_help_message... Options>
    struct usage_helper
    {
        static auto help_message()
        {
            return std::array {Options::help_message()...};
        }
    };
}

void print_usage(const char* name, std::ostream& os = std::cout)
{
    os << "usage: " << name << " <filename> <algorithm> OPTIONS" << std::endl;
    auto opts = extended_options::apply<detail::usage_helper>::help_message();
    size_t maxw = 0;
    for (auto& [opt, _]: opts)
        maxw = std::max(maxw, opt.size());
    
    os << "The options are:" << std::endl;
    for (auto& [opt, desc]: opts)
        os << std::setw(maxw + 5) << std::left << opt << desc << std::endl;
}

//todo: BRIDGE pattern u term
//todo: unit testy
//todo: statistiky (počet otevřených nodů, délka cesty ...)
//todo: další algoritmy :)
//todo: přidat memento, observer bude každý krok zachytavat do mementa -- více módů (volný běh, forward/backward rolling ...)

int main(int argc, char* argv[])
{
    auto parse_result = parse_options(argc, argv);
    if (std::holds_alternative<help>(parse_result))
    {
        print_usage(argv[0]);
        return 0;
    }
    
    auto options_result = std::get<expected<options>>(parse_result);
    if (!options_result)
    {
        std::cout << "error parsing options: " << options_result.error() << std::endl;
        return 1;
    }
    
    if (options_result->nonpositional_arguments.size() != 2)
    {
        print_usage(argv[0]);
        return 1;
    }
    
    auto maze = open_file(options_result->nonpositional_arguments[0])
            .and_then(maze::load_from_stream);
    if (!maze)
    {
        std::cout << "error loading the maze: " << maze.error() << std::endl;
        return 1;
    }
    auto algorithm = pick_algorithm(options_result->nonpositional_arguments[1], options_result->options);
    
    if (!algorithm)
    {
        std::cout << "error picking algorithm: " << algorithm.error() << std::endl;
        return 1;
    }
    runner r(std::move(*algorithm), *maze, options_result->options);
    r.run();
    return 0;
}
