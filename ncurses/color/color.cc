#include "ncurses/color/color.h"

#include <ncurses.h>

namespace runai::ncurses::color
{

void start()
{
    start_color();

    const auto background = use_default_colors() == OK ? -1 : COLOR_BLACK;

    init_pair(static_cast<short>(Color::Black),     COLOR_BLACK,    background);
    init_pair(static_cast<short>(Color::Red),       COLOR_RED,      background);
    init_pair(static_cast<short>(Color::Green),     COLOR_GREEN,    background);
    init_pair(static_cast<short>(Color::Yellow),    COLOR_YELLOW,   background);
    init_pair(static_cast<short>(Color::Blue),      COLOR_BLUE,     background);
    init_pair(static_cast<short>(Color::Magenta),   COLOR_MAGENTA,  background);
    init_pair(static_cast<short>(Color::Cyan),      COLOR_CYAN,     background);
    init_pair(static_cast<short>(Color::White),     COLOR_WHITE,    background);
}

} // namespace runai::ncurses::color
