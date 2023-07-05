#pragma once

#include <functional>
#include <list>
#include <any>


template<typename ... Args>
class event
{
 private:
	struct callback_handle
	{
	 private:
		callback_handle(typename std::list<std::function<void(Args...)>>::iterator iter) : iter_ {iter} { }
		typename std::list<std::function<void(Args...)>>::iterator iter_;
		friend class event;
	};
 public:
	void trigger(auto&& ... args)
	{
		for(auto&& callback: callbacks_)
			callback(FWD(args)...);
	}
	bool deregister_callback(std::any todel)
	{
		try
		{
			callbacks_.erase(std::any_cast<callback_handle&>(todel).iter_);
			return true;
		}
		catch(std::bad_any_cast& e)
		{
			return false;
		}
	}
	template<typename Fn>
	std::any register_callback(Fn&& callback)
	{
		auto iter = callbacks_.insert(callbacks_.end(), std::forward<Fn>(callback));
		return callback_handle {iter};
	}
 private:
	std::list<std::function<void(Args...)>> callbacks_;
};
