#pragma once

#include <memory>
#include "../maze.hpp"
#include "../utility/event.hpp"
#include "../options/opts.hpp"

#define EVENT(name, ...) \
public: \
template<typename Callable> \
void register_##name(Callable&& fn) \
{ \
 name.register_callback(std::forward<Callable>(fn));    \
}                        \
protected:               \
template<typename ...Args>  \
void on_##name(Args&& ... args) \
{ \
    name.trigger(std::forward<Args>(args)...); \
}                        \
private: \
event<__VA_ARGS__> name;


class pf_algorithm
{
 public:
	virtual ~pf_algorithm() = default;
	virtual void run(const maze& maze) = 0;
	template<std::derived_from<pf_algorithm> T>
	static std::unique_ptr<pf_algorithm> make(auto&& ... args)
	{
		return std::make_unique<T>(FWD(args)...);
	}
    virtual std::string description() const = 0;
 protected:
	using seen_matrix = matrix<int8_t>;
	using prev_matrix = matrix<coord>;
	std::pair<prev_matrix, seen_matrix> fresh_all(const maze& maze);
	void reconstruct_path(const maze& maze, const matrix<coord>& prev);
    std::array<std::function<coord(const coord&)>, 4> neighborhood_order_ = {&coord::left, &coord::down, &coord::right, &coord::up};
 EVENT(step)
 EVENT(fresh, const coord&)
 EVENT(open, const coord&)
 EVENT(closed, const coord&)
 EVENT(path, const coord&)
 EVENT(explore, const coord&)
};







