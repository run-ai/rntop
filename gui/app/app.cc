#include "gui/app/app.h"

#include <ncurses.h>

#include "ncurses/color/color.h"

namespace runai::gui
{

App::App(unsigned nodes, unsigned gpus, const Arguments & arguments) :
    _arguments(arguments),
    _ncurses(),
    _cluster(0, 0, 1, 0, "Cluster"),
    _nodes(0, _cluster.y(decltype(_cluster)::Y::End), nodes, 0, "Nodes"),
    _gpus(0, _nodes.y(decltype(_nodes)::Y::End), gpus, 0, "GPUs")
{
    curs_set(0); // make the cursor invisible

    if (_arguments.color)
    {
        ncurses::color::start();
    }
}

void App::refresh(const Cluster & cluster)
{
    _cluster.moveln(0);
    _nodes.moveln(0);
    _gpus.moveln(0);

    _cluster.println(cluster.metric().convert(_arguments.unit));

    for (const auto & node : cluster)
    {
        _nodes.print("%-25s %-11s\t", node.hostname().c_str(), node.driver().c_str());
        _nodes.println(node.metric().convert(_arguments.unit));

        for (const auto & device : node)
        {
            _gpus.print("%-25s", node.hostname().c_str());

            if (_arguments.gpu_index)
            {
                _gpus.print(" %-2d", device.index());
            }

            if (_arguments.gpu_name)
            {
                _gpus.print(" %-30s", device.name().c_str());
            }

            if (_arguments.gpu_uuid)
            {
                _gpus.print(" %s", device.uuid().c_str());
            }

            _gpus.print("\t");
            _gpus.println(device.metric().convert(_arguments.unit));
        }
    }

    _cluster.refresh();
    _nodes.refresh();
    _gpus.refresh();
}

} // namespace runai::gui
