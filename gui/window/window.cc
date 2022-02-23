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

int Window::line() const
{
    return y(Y::Current) - 1;
}

void Window::print(const View & view)
{
    view.print(*this);
}

void Window::fillln(char ch)
{
    hline_(ch, -1);
}

void Window::moveln(int line)
{
    move(_offset, line + 1); // NOLINT(build/include_what_you_use)
}

void Window::nextln()
{
    moveln(line() + 1);
}

void Window::println(int line, const View & view)
{
    moveln(line);
    println(view);
}

void Window::println(const View & view)
{
    print(view);
    fillln();
    nextln();
}

void Window::println(int line, const char * fmt, ...)
{
    moveln(line);

    va_list args;
    va_start(args, fmt);
    vprintln(fmt, args);
    va_end(args);
}

void Window::println(const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintln(fmt, args);
    va_end(args);
}

void Window::vprintln(const char * fmt, va_list args)
{
    vprint(fmt, args);
    fillln();
    nextln();
}

} // namespace runai::gui
