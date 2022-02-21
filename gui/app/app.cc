#include "gui/app/app.h"

#include <ncurses.h>

namespace runai::gui
{

App::App(unsigned nodes) :
    _ncurses(),
    _cluster(0, 0, 1, 0, "Cluster"),
    _nodes(0, _cluster.y(decltype(_cluster)::Y::End), nodes, 0, "Nodes"),
    _gpus(0, _nodes.y(decltype(_nodes)::Y::End), 10, 0, "GPUs")
{
    curs_set(0); // make the cursor invisible
}

void App::update(const Cluster::Snapshot & snapshot)
{
    _cluster.println(0, "GPU utilization: %3d%%    Used GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
        snapshot.utilization,
        snapshot.used_memory,
        snapshot.total_memory,
        static_cast<float>(snapshot.used_memory) / static_cast<float>(snapshot.total_memory) * 100.f);

    unsigned gpu = 0;
    for (unsigned i = 0; i < snapshot.nodes.size(); ++i)
    {
        const auto & pair = snapshot.nodes.at(i);
        const auto & node = *pair.first;
        const auto & snapshot = pair.second;

        for (unsigned j = 0; j < snapshot.devices.size(); ++j)
        {
            const auto & device = snapshot.devices.at(j);

            _gpus.println(gpu++, "%-25s %-2d\tGPU utilization: %3d%%\tUsed GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
                node.hostname().c_str(),
                j,
                device.utilization,
                device.used_memory,
                device.total_memory,
                static_cast<float>(device.used_memory) / static_cast<float>(device.total_memory) * 100.f);
        }

        _nodes.println(i, "%-25s\t%-11s\tGPU utilization: %3d%%\tUsed GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
            node.hostname().c_str(),
            node.driver().c_str(),
            snapshot.utilization,
            snapshot.used_memory,
            snapshot.total_memory,
            static_cast<float>(snapshot.used_memory) / static_cast<float>(snapshot.total_memory) * 100.f);
    }
}

} // namespace runai::gui
