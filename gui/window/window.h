#pragma once

#include <string>

#include "ncurses/window/window.h"

namespace runai::gui
{

struct Window;

struct View
{
    virtual void print(Window & window) const = 0;
};

struct Window : ncurses::Window
{
    Window(int y, int x, int lines, int cols, const std::string & title = {});

    // query

    int line() const;

    // actions

    using ncurses::Window::print;
    void print(const View & view);

    // line actions

    void fillln(char ch = ' ');
    void moveln(int line);
    void nextln();
    void println(int line, const View & view);
    void println(const View & view);
    void println(int line, const char * fmt, ...);
    void println(const char * fmt, ...);
    void vprintln(const char * fmt, va_list args);

 private:
    unsigned _offset = 0;
};

} // namespace runai::gui
