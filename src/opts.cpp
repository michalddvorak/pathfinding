#include "opts.hpp"

#include <string>
#include <sstream>
#include <getopt.h>

#include "utility/expected.hpp"

using namespace std::string_literals;


expected<opt> parse_neighborhood_order(const std::string& arg)
{
	opt_neighborhood_order nb;
	if(auto res = nb.set_permutation(arg); !res)
		return err<opt>(res.error());
	return just(opt {nb});
}
expected<opt> parse_milliseconds(const std::string& arg)
{
	std::stringstream ss {arg};
	unsigned int x;
	if(!(ss >> x))
		return err<opt>("could not parse milliseconds from \"" + arg + "\"");
	return just(opt {opt_sleep_time {x}});
}

std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[])
{
	
	static const struct option long_opts[] = {
			{.name = "neighborhood", .has_arg = required_argument, .flag=nullptr, .val = 'n'},
			{.name = "help", .has_arg = no_argument, .flag = nullptr, .val = 'h'},
			{.name = "sleep_time", .has_arg = required_argument, .flag=nullptr, .val='s'}
	};
	std::vector<opt> opts;
	std::vector<std::string> nonpos_args;
	
	int opt_idx = 0;
	int c;
	while((c = getopt_long(argc, argv, "n:s:h", long_opts, &opt_idx)) != -1)
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
			case 's':
			{
				auto res = parse_milliseconds(optarg);
				if(!res)
					return err<options>("error parsing sleep time option: "s + res.error());
				opts.push_back(*res);
				break;
			}
		}
	}
	
	for(; optind < argc; ++optind)
		nonpos_args.emplace_back(argv[optind]);
	
	
	return just(std::pair {opts, nonpos_args});
}
