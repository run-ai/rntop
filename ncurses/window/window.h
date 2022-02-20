#pragma once

#include <ncurses.h>

namespace runai::ncurses
{

struct Window
{
    Window(int y, int x, int lines, int cols);
    ~Window();

    Window(const Window &) = delete;
    Window & operator=(const Window &) = delete;

    Window(Window &&) = delete;
    Window & operator=(Window &&) = delete;

    operator WINDOW * () { return _window; }

    // queries

    enum class XY
    {
        Current,
        Beginning,
        Max,
        End,
    };

    using X = XY;
    using Y = XY;

    int x(X which) const;
    int y(Y which) const;

    // actions

    void border_(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    void hline_(char ch, int n);
    void move(int x, int y); // NOLINT(build/include_what_you_use)
    void print(const char * fmt, ...);
    void vprint(const char * fmt, va_list args);
    void refresh();

 private:
    WINDOW * _window = nullptr;
};

} // namespace runai::ncurses
