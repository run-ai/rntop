#include "gui/app/app.h"

#include <ncurses.h>

namespace runai::gui
{

App::App(unsigned nodes) :
    _ncurses(),
    _cluster(0, 0, 1, 0, "Cluster"),
    _nodes(0, _cluster.y(decltype(_cluster)::Y::End), nodes, 0, "Nodes"),
    _gpus(0, _nodes.y(decltype(_nodes)::Y::End), 0, 0, "GPUs")
{
    curs_set(0); // make the cursor invisible
}

void App::refresh(const Cluster & cluster)
{
    // cluster window

    const auto metric = cluster.metric();

    _cluster.println(0, "GPU utilization: %3d%%   Used GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
        metric.utilization,
        metric.used_memory,
        metric.total_memory,
        static_cast<float>(metric.used_memory) / static_cast<float>(metric.total_memory) * 100.f);

    unsigned gpu = 0; // line

    for (unsigned i = 0; i < cluster.count(); ++i)
    {
        const auto & node = cluster.node(i);

        // nodes window

        const auto metric = node.metric();

        _nodes.println(i, "%-25s %-11s\tGPU utilization: %3d%%\tUsed GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
            node.hostname().c_str(),
            node.driver().c_str(),
            metric.utilization,
            metric.used_memory,
            metric.total_memory,
            static_cast<float>(metric.used_memory) / static_cast<float>(metric.total_memory) * 100.f);

        // GPUs window

        for (const auto & device : node)
        {
            const auto metric = device.metric();

            _gpus.println(gpu++, "%-25s %-2d\tGPU utilization: %3d%%\tUsed GPU memory: %5d MiB / %-5d MiB (%.0f%%)",
                node.hostname().c_str(),
                device.index(),
                metric.utilization,
                metric.used_memory,
                metric.total_memory,
                static_cast<float>(metric.used_memory) / static_cast<float>(metric.total_memory) * 100.f);
        }
    }
}

} // namespace runai::gui
