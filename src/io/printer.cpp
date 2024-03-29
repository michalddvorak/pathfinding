#include "printer.hpp"

const std::string printer::EXPLORING = with_fg_color({.r = 0, .g = 255, .b = 0})("@");
const std::string printer::CLOSED = with_fg_color({.r = 255, .g = 0, .b = 255})("#");
const std::string printer::OPEN = with_fg_color({.r = 255, .g = 0, .b = 0})("O");
const std::string printer::START = with_fg_color({.r = 255, .g = 255, .b = 0})("S");
const std::string printer::END = with_fg_color({.r = 255, .g = 255, .b = 0})("E");
const std::string printer::WALL = with_bg_color({.r = 0, .g = 0, .b = 0})(" ");
const std::string printer::PATH = with_blink()(with_fg_color({.r = 0, .g = 0, .b = 255})("o"));

printer::printer(const maze* maze, pf_algorithm* algorithm, const std::vector<opt>& options) : maze_ {maze},
                                                                                               algorithm_ {algorithm}
{
    parse_options(options);
    algorithm->register_path(path_callback());
    algorithm->register_fresh(fresh_callback());
    algorithm->register_closed(closed_callback());
    algorithm->register_open(open_callback());
    algorithm->register_explore(explore_callback());
}

void printer::parse_options(const std::vector<opt>& options)
{

}

void printer::print_maze()
{
    set_cursor({0, 0});
    for (size_t i = 0; i < maze_->mat.rows(); ++i)
    {
        for (size_t j = 0; j < maze_->mat.cols(); ++j)
        {
            set_cursor({i, j});
            switch (maze_->mat(i, j))
            {
                case maze_object::wall:
                    std::cout << WALL;
                    break;
                case maze_object::free:
                    std::cout << ' ';
                    break;
            }
        }
        std::cout << '\n';
    }
    print(maze_->start, START);
    print(maze_->end, END);
}

void printer::print_description()
{
    std::cout << START << " - start, "
              << END << " - end, "
              << EXPLORING << " - exploring, "
              << CLOSED << " - closed, "
              << OPEN << " - open, "
              << PATH << " - path, "
              << WALL << " - wall" << std::endl;
}
