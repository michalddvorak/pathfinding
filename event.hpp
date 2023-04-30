#pragma once

#include <functional>
#include <list>

template<typename ... Args>
class event
{
 public:
	template<typename... Ts>
	void trigger(Ts&& ... args)
	{
		for(auto&& callback: callbacks_)
			callback(std::forward<Ts>(args)...);
	}
	template<typename Fn>
	void register_callback(Fn&& callback)
	{
		callbacks_.push_back(std::forward<Fn>(callback));
	}
 private:
	std::vector<std::function<void(Args...)>> callbacks_;
};
