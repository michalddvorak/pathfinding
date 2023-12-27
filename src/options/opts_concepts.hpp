#include <type_traits>

#pragma once
template <typename T>
concept parseable =
requires(const char* arg)
{
    { T::parse(arg) } -> std::same_as<expected<T>>;
};

template <typename T, typename OptionInfo>
concept has_opt =
requires
{
    { T::opt } -> std::convertible_to<OptionInfo>;
};

template <typename T>
concept has_help_message =
requires
{
    { T::help_message() } -> std::same_as<std::pair<std::string, std::string>>;
};

template <typename T, typename OptionInfo>
concept option_like = parseable<T> && has_opt<T, OptionInfo> && has_help_message<T>;


template <typename T, typename OptionInfo>
concept help_like = has_opt<T, OptionInfo> && has_help_message<T>;


