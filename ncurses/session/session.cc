#include "ncurses/session/session.h"

namespace runai::ncurses
{

Session::Session()
{
    initscr();
}

Session::~Session()
{
    endwin();
}

} // namespace runai::ncurses
