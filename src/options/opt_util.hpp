#pragma once

#include <string>
#include <getopt.h>

std::string construct_shortopts(const struct option* long_opts);

std::string construct_argument_help(const struct option& opt);