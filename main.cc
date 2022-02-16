#include <unistd.h>

#include <iostream>

#include "arguments/arguments.h"
#include "cluster/cluster.h"

namespace runai
{

void run(const Cluster & cluster)
{
    const auto snapshot = cluster.snapshot();

    for (const auto & pair : snapshot.nodes)
    {
        const auto & node = *pair.first;
        const auto & snapshot = pair.second;

        std::cout << node.hostname() << " (" << node.driver() << ")" << std::endl;

        for (unsigned i = 0; i < snapshot.devices.size(); ++i)
        {
            const auto & device = snapshot.devices.at(i);

            std::cout << "  GPU " << i << " utilization " << device.utilization << "% used memory " << device.used_memory << " MiB / " << device.total_memory << " MiB" << std::endl;
        }

        std::cout << "  node avg. GPU utilization " << snapshot.utilization << "% total used memory " << snapshot.used_memory << " MiB / " << snapshot.total_memory << " MiB" << std::endl;
    }

    std::cout << "cluster avg. GPU utilization " << snapshot.utilization << "% total used memory " << snapshot.used_memory << " MiB / " << snapshot.total_memory << " MiB" << std::endl;
}

extern "C" int main(int argc, char * argv[])
{
    const auto arguments = Arguments::parse(argc, argv);

    const auto cluster = Cluster(arguments.hostnames);

    while (true)
    {
        run(cluster);

        if (arguments.interval <= 0)
        {
            break;
        }

        sleep(arguments.interval);
    }

    return EXIT_SUCCESS;
}

} // namespace runai
