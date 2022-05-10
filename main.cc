#include <unistd.h>

#include "arguments/arguments.h"
#include "cluster/cluster.h"
#include "logger/logger.h"
#include "thread/thread.h"

#include "gui/app/app.h"

namespace runai
{

extern "C" int main(int argc, char * argv[])
{
    const auto arguments = Arguments::parse(argc, argv);

    // initialize the output file
    Logger::init(arguments.output);

    // connect to all the nodes in the cluster and gather the initial information
    auto cluster = Cluster(arguments.hostnames, arguments.username, arguments.agent, Cluster::Config { .output_every = arguments.output_every });

    // start the GUI application
    auto app = gui::App(cluster.nodes(), cluster.gpus(), arguments);

    // now we are going to launch threads for updating metrics
    auto watchers = std::vector<Thread>();

    // a thread for the cluster
    watchers.emplace_back(std::bind(&Cluster::refresh, std::ref(cluster)), arguments.interval);

    // a thread per node
    for (auto & node : cluster)
    {
        watchers.emplace_back(std::bind(&Node::refresh, std::ref(node)), arguments.interval);
    }

    // refresh the GUI application once a second and we are good to go
    while (true)
    {
        app.refresh(cluster);

        sleep(1); // this is not defined by the user specified interval
    }

    return EXIT_SUCCESS;
}

} // namespace runai
