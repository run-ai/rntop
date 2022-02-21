#include <unistd.h>

#include "arguments/arguments.h"
#include "cluster/cluster.h"

#include "gui/app/app.h"

namespace runai
{

extern "C" int main(int argc, char * argv[])
{
    const auto arguments = Arguments::parse(argc, argv);

    const auto cluster = Cluster(arguments.hostnames, arguments.username, arguments.agent);

    auto app = gui::App(cluster.size());

    while (true)
    {
        const auto snapshot = cluster.snapshot();

        app.update(snapshot);

        if (arguments.interval <= 0)
        {
            break;
        }

        sleep(arguments.interval);
    }

    return EXIT_SUCCESS;
}

} // namespace runai
