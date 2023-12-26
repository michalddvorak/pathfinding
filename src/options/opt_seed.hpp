struct opt_seed
{
    unsigned long seed;
    
    static expected<opt_seed> parse(const char* arg)
    {
        using namespace std::string_literals;
        return parse_string<unsigned long>(arg, "could not seed from \""s + arg + "\"")
                .and_then(
                        [&](unsigned long x)
                        {
                            return just(opt_seed {x});
                        });
    }
    
    static std::pair<std::string, std::string> help_message()
    {
        return {"-d|--seed NUM", "seeds the random number generator"};
    }
    
    static constexpr struct option opt = {.name = "seed", .has_arg = required_argument, .flag=nullptr, .val='d'};
};