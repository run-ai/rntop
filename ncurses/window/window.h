#pragma once

#include <ncurses.h>

#include "ncurses/color/color.h"

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

    struct Attr
    {
        Attr() = default;
        Attr(Window & window, attr_t attr);
        ~Attr();

        Attr(const Attr &) = delete;
        Attr & operator=(const Attr &) = delete;

        Attr(Attr &&);
        Attr & operator=(Attr &&);

     private:
        Window * _window = nullptr;
        attr_t _attr;
    };

    Attr attr(attr_t attr_);
    void attron_(attr_t attr);
    void attroff_(attr_t attr);
    void border_(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    Attr color(Color color);
    void hline_(char ch, int n);
    void move(int x, int y); // NOLINT(build/include_what_you_use)
    void print(const char * fmt, ...);
    void print(Color color, const char * fmt, ...);
    void vprint(const char * fmt, va_list args);
    void refresh();

 private:
    WINDOW * _window = nullptr;
};

} // namespace runai::ncurses
