#pragma once

#include <string>
#include <variant>
#include <functional>

template<typename T=void, typename Err = std::string>
struct expected
{
 private:
	struct unexpected
	{
		Err err;
	};
 public:
	template<typename ...Args>
	static expected just(Args&& ... args)
	{
		return expected {T {std::forward<Args>(args)...}};
	}
	template<typename ...Args>
	static expected err(Args&& ... args)
	{
		return expected {unexpected {{std::forward<Args>(args)...}}};
	}
	template<typename F, typename ...Args>
	decltype(auto) and_then(F&& fn, Args&& ... args)&&
	{
		using ret = decltype(std::forward<F>(fn)(std::move(value()), std::forward<Args>(args)...));
		if(*this)
			return std::forward<F>(fn)(std::move(value()), std::forward<Args>(args)...);
		else
			return ret::err(std::move(error()));
	}
	template<typename F, typename ...Args>
	decltype(auto) and_then(F&& fn, Args&& ... args)&
	{
		using ret = decltype(std::forward<F>(fn)(value(), std::forward<Args>(args)...));
		if(*this)
			return std::forward<F>(fn)(value(), std::forward<Args>(args)...);
		else
			return ret::err(error());
	}
	
	operator bool() const
	{
		return std::holds_alternative<T>(value_);
	}
	const T& operator *() const
	{
		return value();
	}
	T& operator *()
	{
		return value();
	}
	const T& value() const
	{
		return std::get<T>(value_);
	}
	T& value()
	{
		return std::get<T>(value_);
	}
	const Err& error() const
	{
		return std::get<unexpected>(value_).err;
	}
 private:
	Err& error()
	{
		return std::get<unexpected>(value_).err;
	}
	expected(std::variant<T, unexpected> v) : value_(std::move(v)) { }
	std::variant<T, unexpected> value_ = T();
};

template<typename Err>
struct expected<void, Err>
{
 private:
	struct unexpected
	{
		Err err;
	};
 public:
	expected(bool v = true, std::string msg = "") : value_ {v ? static_cast<std::optional<unexpected>>(std::nullopt)
															  : unexpected {std::move(msg)}} { }
	template<typename ...Args>
	static expected just(Args&& ... args)
	{
		return expected {std::nullopt};
	}
	template<typename ...Args>
	static expected err(Args&& ... args)
	{
		return expected {unexpected {{std::forward<Args>(args)...}}};
	}
	template<typename F, typename ...Args>
	decltype(auto) and_then(F&& fn, Args&& ... args)
	{
		using ret = decltype(std::forward<F>(fn)(std::forward<Args>(args)...));
		if(*this)
			return std::forward<F>(fn)(std::forward<Args>(args)...);
		else
			return ret::err(error());
	}
	
	void operator *() const { }
	void value() const { }
	operator bool() const
	{
		return value_ == std::nullopt;
	}
	const Err& error() const
	{
		return value_->err;
	}
 private:
	expected(std::optional<unexpected> v) : value_(std::move(v)) { }
	std::optional<unexpected> value_ = std::nullopt;
};

expected() -> expected<void>;

template<typename T = void, typename Err = std::string>
auto just()
{
	return expected<T, Err>::just();
}


template<typename Arg, typename Err = std::string>
auto just(Arg&& arg)
{
	return expected<std::decay_t<Arg>, Err>::just(std::forward<Arg>(arg));
}

template<typename T = void, typename Err = std::string, typename ...Args>
auto err(Args&& ... args)
{
	return expected<T, Err>::err(std::forward<Args>(args)...);
}
