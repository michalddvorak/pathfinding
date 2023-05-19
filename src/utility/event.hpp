#pragma once

#include <functional>
#include <list>
#include <any>


template<typename ... Args>
class event
{
 public:
	struct callback_handle
	{
	 private:
		callback_handle(typename std::list<std::function<void(Args...)>>::iterator iter) : iter_ {iter} { }
		typename std::list<std::function<void(Args...)>>::iterator iter_;
		friend class event;
	};
	template<typename... Ts>
	void trigger(Ts&& ... args)
	{
		for(auto&& callback: callbacks_)
			callback(std::forward<Ts>(args)...);
	}
	void deregister_callback(callback_handle todel)
	{
		callbacks_.erase(todel.iter_);
	}
	template<typename Fn>
	callback_handle register_callback(Fn&& callback)
	{
		auto iter = callbacks_.insert(callbacks_.end(), std::forward<Fn>(callback));
		return callback_handle {iter};
	}
 private:
	std::list<std::function<void(Args...)>> callbacks_;
};
