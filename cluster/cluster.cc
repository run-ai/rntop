#include "cluster/cluster.h"

#include "utils/utils.h"

namespace runai
{

Cluster::Cluster(const std::vector<std::string> & hostnames, const std::string & username, const agent::Factory & factory)
{
    for (const auto & hostname : hostnames)
    {
        _nodes.emplace_back(hostname, factory.create(hostname, username));
    }
}

void Cluster::refresh()
{
    using Op = utils::Op<size_t, Node>;

    _metric.store(
        {
            // TODO(raz): theoretically, a node metric can change while we are calculating the cluster metric.
            //            we should consider copying the node metrics for the cluster metric to be coherent.

            .utilization  = utils::avg(_nodes, (Op)[](const auto & node){ return node.metric().utilization;  }),
            .used_memory  = utils::sum(_nodes, (Op)[](const auto & node){ return node.metric().used_memory;  }),
            .total_memory = utils::sum(_nodes, (Op)[](const auto & node){ return node.metric().total_memory; }),
        });
}

} // namespace runai
