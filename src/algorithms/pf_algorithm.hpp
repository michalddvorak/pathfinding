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
	template<typename T>
	static auto make(const std::vector<opt>& options)
	{
		return just<std::unique_ptr<pf_algorithm>>(std::make_unique<T>(options));
	}
 protected:
	using seen_matrix = matrix<int8_t>;
	using prev_matrix = matrix<coord>;
	std::pair<prev_matrix, seen_matrix> fresh_all(const maze& maze);
	void reconstruct_path(const maze& maze, const matrix<coord>& prev);
 
 EVENT(step)
 EVENT(fresh, const coord&)
 EVENT(open, const coord&)
 EVENT(closed, const coord&)
 EVENT(path, const coord&)
};







