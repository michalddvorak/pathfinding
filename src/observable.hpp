#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

template<typename ... Args>
class observer
{
 public:
	virtual ~observer() = default;
	virtual void on_event(Args ...) = 0;
};

template<typename... Args>
class event
{
 public:
	event& register_observer(observer<Args...>* observer)
	{
		m_observers.push_back(observer);
		return *this;
	}
	void trigger(Args ... args)
	{
		for(const auto& observer: m_observers)
			observer->on_event(args ...);
	}
 private:
	std::vector<observer<Args...>*> m_observers;
};




