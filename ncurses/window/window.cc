#include "ncurses/window/window.h"

#include <iostream>
#include <utility>

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

Window::Attr Window::attr(attr_t attr_)
{
    return Attr(*this, attr_);
}

void Window::attron_(attr_t attr)
{
    if (wattron(_window, attr) == ERR)
    {
        std::cerr << "wattron() failed" << std::endl;
        throw std::exception();
    }
}

void Window::attroff_(attr_t attr)
{
    if (wattroff(_window, attr) == ERR)
    {
        std::cerr << "wattroff() failed" << std::endl;
        throw std::exception();
    }
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

Window::Attr Window::color(Color color)
{
    return color == Color::None ? Attr() : attr(COLOR_PAIR(static_cast<int>(color)));
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

void Window::print(Color color_, const char * fmt, ...)
{
    const auto attr = color(color_);

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

Window::Attr::Attr(Window & window, attr_t attr) :
    _window(&window),
    _attr(attr)
{
    _window->attron_(_attr);
}

Window::Attr::~Attr()
{
    if (_window != nullptr)
    {
        _window->attroff_(_attr);
    }
}

Window::Attr::Attr(Attr && other)
{
    *this = std::move(other);
}

Window::Attr & Window::Attr::operator=(Attr && other)
{
    if (_window != nullptr)
    {
        _window->attroff_(_attr);
    }

    _window = other._window;
    _attr = other._attr;

    other._window = nullptr;

    return *this;
}

} // namespace runai::ncurses
