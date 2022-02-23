#pragma once

#include "cluster/cluster.h"

#include "gui/window/window.h"

#include "ncurses/session/session.h"

namespace runai::gui
{

struct App
{
    App(unsigned nodes, bool color);

    void refresh(const Cluster & cluster);

 private:
    ncurses::Session _ncurses;
    gui::Window _cluster;
    gui::Window _nodes;
    gui::Window _gpus;
};

} // namespace runai::gui
