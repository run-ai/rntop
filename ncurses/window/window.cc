#include "ncurses/window/window.h"

#include <iostream>

namespace runai::ncurses
{

Window::Window(int x, int y, int lines, int cols) :
    _window(newwin(lines, cols, y, x))
{
    if (_window == nullptr)
    {
        std::cerr << "newwin() failed" << std::endl;
        throw std::exception();
    }
}

Window::~Window()
{
    if (delwin(_window) == ERR)
    {
        std::cerr << "delwin() failed" << std::endl;
    }
}

int Window::x(X which) const
{
    if (which == X::End)
    {
        return x(X::Beginning) + x(X::Max);
    }

    int x_;

    if (which == X::Beginning)
    {
        x_ = getbegx(_window);
    }
    else if (which == X::Current)
    {
        x_ = getcurx(_window);
    }
    else if (which == X::Max)
    {
        x_ = getmaxx(_window);
    }
    else
    {
        std::cerr << "Invalid argument (" << static_cast<int>(which) << ")" << std::endl;
        throw std::exception();
    }

    if (x_ == ERR)
    {
        std::cerr << "get*x() failed" << std::endl;
        throw std::exception();
    }

    return x_;
}

int Window::y(Y which) const
{
    if (which == Y::End)
    {
        return y(Y::Beginning) + y(Y::Max);
    }

    int y_;

    if (which == Y::Beginning)
    {
        y_ = getbegy(_window);
    }
    else if (which == Y::Current)
    {
        y_ = getcury(_window);
    }
    else if (which == Y::Max)
    {
        y_ = getmaxy(_window);
    }
    else
    {
        std::cerr << "Invalid argument (" << static_cast<int>(which) << ")" << std::endl;
        throw std::exception();
    }

    if (y_ == ERR)
    {
        std::cerr << "get*y() failed" << std::endl;
        throw std::exception();
    }

    return y_;
}

void Window::border_(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br)
{
    if (wborder(_window, ls, rs, ts, bs, tl, tr, bl, br) == ERR)
    {
        std::cerr << "wborder() failed" << std::endl;
        throw std::exception();
    }
}

void Window::hline_(char ch, int n)
{
    if (n < 0)
    {
        n += x(ncurses::Window::X::Max) - x(ncurses::Window::X::Current);
    }

    if (whline(_window, ch, n) == ERR)
    {
        std::cerr << "whline() failed" << std::endl;
        throw std::exception();
    }
}

void Window::move(int x, int y) // NOLINT(build/include_what_you_use)
{
    if (wmove(_window, y, x) == ERR)
    {
        std::cerr << "wmove() failed" << std::endl;
        throw std::exception();
    }
}

void Window::print(const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprint(fmt, args);
    va_end(args);
}

void Window::vprint(const char * fmt, va_list args)
{
    if (vw_printw(_window, fmt, args) == ERR)
    {
        std::cerr << "vw_printw() failed" << std::endl;
        throw std::exception();
    }
}

void Window::refresh()
{
    if (wrefresh(_window) == ERR)
    {
        std::cerr << "wrefresh() failed" << std::endl;
        throw std::exception();
    }
}

} // namespace runai::ncurses
