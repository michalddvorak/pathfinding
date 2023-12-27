#include "opts.hpp"

std::variant<help, expected<options>> parse_options(int argc, char** argv)
{
    return extended_options::apply<option_parser>::parse(argc, argv);
}
