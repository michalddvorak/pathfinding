#include "opts.hpp"

#include <string>
#include <map>

#include <getopt.h>

#include "utility/expected.hpp"
#include "coord.hpp"

using namespace std::string_literals;



expected<opt> parse_neighborhood_order(const std::string& arg)
{

}

std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[])
{
	
	static const struct option long_opts[] = {
			{.name = "neighborhood", .has_arg = required_argument, .flag=nullptr, .val = 'n'},
			{.name = "help", .has_arg = no_argument, .flag = nullptr, .val = 'h'}
	};
	std::vector<opt> opts;
	std::vector<std::string> nonpos_args;
	
	int opt_idx = 0;
	int c;
	while((c = getopt_long(argc, argv, "n:h", long_opts, &opt_idx)) != -1)
	{
		switch(c)
		{
			case 'n':
			{
				auto res = parse_neighborhood_order(optarg);
				if(!res)
					return err<options>("error parsing neighborhood option: "s + res.error());
				opts.push_back(*res);
				break;
			}
			case 'h':
				return help_tag {};
		}
	}
	
	for(; optind < argc; ++optind)
		nonpos_args.emplace_back(argv[optind]);
	
	
	return just(std::pair {opts, nonpos_args});
}
