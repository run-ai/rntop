#pragma once

#include <string>

#include "ncurses/window/window.h"

namespace runai::gui
{

struct Window : ncurses::Window
{
    Window(int y, int x, int lines, int cols, const std::string & title = {});

    void println(int line, const char * fmt, ...);

 private:
    unsigned _offset = 0;
};

} // namespace runai::gui
