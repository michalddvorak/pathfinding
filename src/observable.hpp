#pragma once

#include <vector>
#include <memory>
#include <algorithm>

template<typename ... UpdateArgs>
class observer
{
 public:
	virtual ~observer() = default;
	virtual void update(const UpdateArgs& ...) = 0;
};

template<typename... NotifyArgs>
class observable
{
 public:
	virtual ~observable() = default;
	void register_observer(std::unique_ptr<observer<NotifyArgs...>> observer)
	{
		m_observers.push_back(move(observer));
	}
	void notify_observers(const NotifyArgs& ... args)
	{
		for(const auto& observer: m_observers)
			observer->update(args ...);
	}
 private:
	std::vector<std::unique_ptr<observer<NotifyArgs...>>> m_observers;
};




