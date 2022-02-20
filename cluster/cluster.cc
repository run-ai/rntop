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

Cluster::Snapshot Cluster::snapshot() const
{
    decltype(Snapshot::nodes) nodes_;

    for (const auto & node : _nodes)
    {
        nodes_.push_back(std::make_pair(&node, node.snapshot()));
    }

    using Op = utils::Op<size_t, decltype(nodes_)::value_type>;

    return Snapshot
        {
            .nodes        = nodes_,
            .utilization  = utils::avg(nodes_, (Op)[](const auto & pair){ return pair.second.utilization;  }),
            .used_memory  = utils::sum(nodes_, (Op)[](const auto & pair){ return pair.second.used_memory;  }),
            .total_memory = utils::sum(nodes_, (Op)[](const auto & pair){ return pair.second.total_memory; }),
        };
}

} // namespace runai
