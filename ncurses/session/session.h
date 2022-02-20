#pragma once

#include <ncurses.h>

namespace runai::ncurses
{

struct Session
{
    Session();
    ~Session();

    Session(const Session &) = delete;
    Session & operator=(const Session &) = delete;

    Session(Session &&) = delete;
    Session & operator=(Session &&) = delete;
};

} // namespace runai::ncurses
