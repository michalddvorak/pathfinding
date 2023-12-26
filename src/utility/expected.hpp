#pragma once

#include <string>
#include <variant>
#include <optional>

#include "fwd.hpp"

template <typename T=void, typename Err = std::string>
struct expected
{
  private:
    struct unexpected
    {
        Err err;
    };
  public:
    static expected just(auto&& ... args)
    {
        return expected {T {FWD(args)...}};
    }
    
    static expected err(auto&& ... args)
    {
        return expected {unexpected {{FWD(args)...}}};
    }
    
    decltype(auto) and_then(auto&& fn, auto&& ... args)&&
    {
        using ret = decltype(FWD(fn)(std::move(value()), FWD(args)...));
        if (*this)
            return FWD(fn)(std::move(value()), FWD(args)...);
        else
            return ret::err(std::move(error()));
    }
    
    decltype(auto) and_then(auto&& fn, auto&& ... args)&
    {
        using ret = decltype(FWD(fn)(value(), FWD(args)...));
        if (*this)
            return FWD(fn)(value(), FWD(args)...);
        else
            return ret::err(error());
    }
    
    operator bool() const
    {
        return std::holds_alternative<T>(value_);
    }
    
    const T& operator*() const
    {
        return value();
    }
    
    T& operator*()
    {
        return value();
    }
    
    const T* operator->() const
    {
        return &value();
    }
    
    T* operator->()
    {
        return &value();
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
    
    Err& error()
    {
        return std::get<unexpected>(value_).err;
    }
  
  private:
    expected(std::variant<T, unexpected>&& value) : value_ {std::move(value)} { }
    
    std::variant<T, unexpected> value_;
};

template <typename Err>
struct expected<void, Err>
{
  private:
    struct unexpected
    {
        Err err;
    };
  public:
    static expected just()
    {
        return expected {std::nullopt};
    }
    
    static expected err(auto&& ... args)
    {
        return expected {unexpected {{FWD(args)...}}};
    }
    
    decltype(auto) and_then(auto&& fn, auto&& ... args)
    {
        using ret = decltype(FWD(fn)(FWD(args)...));
        if (*this)
            return FWD(fn)(FWD(args)...);
        else
            return ret::err(error());
    }
    
    void operator*() const { }
    
    void value() const { }
    
    nullptr_t operator->() const
    {
        return nullptr;
    }
    
    nullptr_t operator->()
    {
        return nullptr;
    }
    
    operator bool() const
    {
        return !value_.has_value();
    }
    
    const Err& error() const
    {
        return value_->err;
    }
    
    Err& error()
    {
        return value_->err;
    }
  
  private:
    expected(std::optional<unexpected>&& v) : value_(std::move(v)) { }
    
    std::optional<unexpected> value_ = std::nullopt;
};

template<typename Err>
inline const expected<void, Err>& operator||(const expected<void, Err>& a, const expected<void, Err>& b)
{
    if(!a)
        return a;
    return b;
}


expected() -> expected<void>;


template <typename T = void, typename Err = std::string>
auto just()
{
    return expected<T, Err>::just();
}

template <typename Err = std::string>
auto just(auto&& arg)
{
    return expected<std::decay_t<decltype(arg)>, Err>::just(FWD(arg));
}

template <typename T = void, typename Err = std::string>
auto err(auto&& ...args)
{
    return expected<T, Err>::err(FWD(args)...);
}

/**
 * @brief Takes a function returning bool and lifts it to the expected<void> world with given error message.
 * Formally, given T... -> bool, Err, returns T... -> expected<void,Err>
 * @tparam Err
 * @param f
 * @param error_msg
 * @return
 */

template <typename Err = std::string>
auto boolean_lift(auto&& fn, const Err& error_msg = Err())
{
    return [&](auto&& ... args) -> expected<void, Err>
    {
        if (FWD(fn)(FWD(args)...))
            return expected<void, Err>::just();
        else
            return expected<void, Err>::err(error_msg);
    };
}
