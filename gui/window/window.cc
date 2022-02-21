#include "gui/window/window.h"

namespace runai::gui
{

Window::Window(int x, int y, int lines, int cols, const std::string & title) :
    ncurses::Window(x, y, lines == 0 ? lines : lines + 2 /* border */, cols == 0 ? cols : cols + 2)
{
    border_(0, 0, 0, 0, 0, 0, 0, 0);

    if (!title.empty())
    {
        move(1, 0); // NOLINT(build/include_what_you_use)
        print(" %s ", title.c_str());
        _offset = title.size() + 3;
    }

    refresh();
}

void Window::println(int line, const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    move(_offset, line + 1); // NOLINT(build/include_what_you_use)
    vprint(fmt, args);
    hline_(' ', -1);
    refresh();

    va_end(args);
}

} // namespace runai::gui
