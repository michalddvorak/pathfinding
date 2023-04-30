#pragma once

#include "maze.hpp"
#include "event.hpp"

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

//todo write it manually :)

struct pf_algorithm
{
 public:
	virtual ~pf_algorithm() = default;
	pf_algorithm(maze&& maze);
	virtual void run() = 0;
 	const maze& get_maze() const;
 protected:
	maze maze_;
	void reconstruct_path(const matrix<coord>& prev);
 
 EVENT(step)
 EVENT(fresh, const coord&)
 EVENT(open, const coord&)
 EVENT(closed, const coord&)
 EVENT(path, const coord&)
};





