#include "opts.hpp"

#include <string>
#include <map>
#include <functional>
#include <getopt.h>


using namespace std::string_literals;

expected<opt> parse_sleep_time(const char* arg)
{
	return parse<unsigned int>(arg, "could not parse milliseconds from \""s + arg + "\"")
			.and_then(
					[&](unsigned int x) {
						return just(opt {opt_sleep_time {std::chrono::milliseconds(x)}});
					});
}

expected<opt> parse_nb_order(const std::string& arg)
{
	opt_neighborhood_order result;
	const std::map<char, std::function<coord(const coord&)>> fns =
			{
					{'l', &coord::left},
					{'r', &coord::right},
					{'u', &coord::up},
					{'d', &coord::down}
			};
	
	return boolean_lift(is_same_up_to_permutation, "invalid permutation \"" + arg + "\", it must be a permutation of \"lrud\"")(arg, "lrud")
			.and_then(
					[&]() {
						opt_neighborhood_order result;
						std::transform(arg.begin(), arg.end(), result.order.begin(),
									   [&](char c) { return fns.at(c); });
						return just(opt {result});
					});
}


/**
 * @brief Function processes option as specified by a callback.
 * @param result options struct
 * @param callback function expecting an argument to a option and returning an option (if successful)
 * @return nothing on success, error message on failure
 */
expected<void> process_option(options& result, const std::function<expected<opt>(const char*)>& callback)
{
	return callback(optarg)
			.and_then(
					[&](const opt& opt)->expected<void> {
						result.options.push_back(opt);
						return just();
					});
}

std::variant<help_tag, expected<options>> parse_options(int argc, char* argv[])
{
	static const struct option long_opts[] = {
			{.name = "neighborhood", .has_arg = required_argument, .flag=nullptr, .val = 'n'},
			{.name = "help", .has_arg = no_argument, .flag = nullptr, .val = 'h'},
			{.name = "sleep_time", .has_arg = required_argument, .flag=nullptr, .val='s'},
			{0, 0, 0, 0}
	};
	
	std::map<char, const std::function<expected<opt>(const char*)>> process_opt =
			{
					{'n', parse_nb_order},
					{'s', parse_sleep_time}
			};
	
	options result;
	int opt_idx = 0;
	int c;
	opterr = 0;
	//: as a first character of optstring assures that ':' is returned if argument of an option is missing
	while((c = getopt_long(argc, argv, ":n:s:h", long_opts, &opt_idx)) != -1)
	{
		if(process_opt.count(c) == 1)
		{
			auto res = process_option(result, process_opt.at(c));
			if(!res)
				return err<options>(res.error());
		}
		else
			switch(c)
			{
				case 'h':
					return help_tag {};
				case '?':
					return err<options>("unknown option "s + argv[optind - 1]);
				case ':':
					return err<options>("missing argument to option "s + (char)optopt);
			}
	}
	
	for(; optind < argc; ++optind)
		result.nonpositional_arguments.emplace_back(argv[optind]);
	return just(result);
}
