#include "gui/app/app.h"

#include <ncurses.h>

#include "ncurses/color/color.h"

namespace runai::gui
{

App::App(unsigned nodes, bool color) :
    _ncurses(),
    _cluster(0, 0, 1, 0, "Cluster"),
    _nodes(0, _cluster.y(decltype(_cluster)::Y::End), nodes, 0, "Nodes"),
    _gpus(0, _nodes.y(decltype(_nodes)::Y::End), 0, 0, "GPUs")
{
    curs_set(0); // make the cursor invisible

    if (color)
    {
        ncurses::color::start();
    }
}

void App::refresh(const Cluster & cluster)
{
    _cluster.moveln(0);
    _nodes.moveln(0);
    _gpus.moveln(0);

    _cluster.println(cluster.metric());

    for (const auto & node : cluster)
    {
        _nodes.print("%-25s %-11s\t", node.hostname().c_str(), node.driver().c_str());
        _nodes.println(node.metric());

        for (const auto & device : node)
        {
            _gpus.print("%-25s %-2d\t", node.hostname().c_str(), device.index());
            _gpus.println(device.metric());
        }
    }

    _cluster.refresh();
    _nodes.refresh();
    _gpus.refresh();
}

} // namespace runai::gui
