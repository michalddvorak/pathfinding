#pragma once
namespace detail
{
	struct impossible_struct { };
}

template<typename ...Ts>
concept default_overloaded = (std::is_invocable_v<Ts, detail::impossible_struct> || ...);

template<typename ...Ts>
struct overload : Ts ...
{
	using Ts::operator ()...;
	void operator ()(auto&& ...) { }
};

template<typename ...Ts> requires default_overloaded<Ts...>
struct overload<Ts...> : Ts ...
{
	using Ts::operator ()...;
};

template<typename ...Ts>
overload(Ts...) -> overload<Ts...>;