#include "cluster/cluster.h"

#include "utils/utils.h"

namespace runai
{

Cluster::Cluster(const std::vector<std::string> & hostnames, const std::string & username, const agent::Factory & factory, const Config & config)
{
    for (const auto & hostname : hostnames)
    {
        auto hostname_ = hostname;
        auto username_ = username;

        const auto split = utils::string::split(hostname, '@');

        if (split.size() == 2)
        {
            username_ = split.at(0);
            hostname_ = split.at(1);
        }

        _nodes.emplace_back(hostname_, factory.create(hostname_, username_), config);
    }
}

void Cluster::refresh()
{
    _metric.store(
        {
            // TODO(raz): theoretically, a node metric can change while we are calculating the cluster metric.
            //            we should consider copying the node metrics for the cluster metric to be coherent.

            .utilization  = utils::avg(_nodes, (utils::Op<size_t, Node>)[](const auto & node){ return node.metric().utilization;  }),
            .used_memory  = utils::sum(_nodes, (utils::Op<double, Node>)[](const auto & node){ return node.metric().used_memory;  }),
            .total_memory = utils::sum(_nodes, (utils::Op<double, Node>)[](const auto & node){ return node.metric().total_memory; }),
            .unit         = Unit::MiB,
        });
}

} // namespace runai
