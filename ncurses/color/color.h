#pragma once

namespace runai::ncurses
{

enum class Color : short
{
    None = 0,

    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
};

namespace color
{

void start();

} // namespace color

} // namespace runai::ncurses
