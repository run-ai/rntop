#pragma once

#include <string>
#include <vector>

#include "agent/factory/factory.h"
#include "metric/metric.h"
#include "node/node.h"

namespace runai
{

struct Cluster
{
    Cluster(const std::vector<std::string> & hostnames, const std::string & username, const agent::Factory & factory);

    struct Metric
    {
        size_t utilization;
        size_t used_memory;
        size_t total_memory;
    };

    // queries

    Metric metric() const { return _metric; }

    // access

    auto begin() const { return _nodes.begin(); }
    auto begin()       { return _nodes.begin(); }

    auto end() const { return _nodes.end();   }
    auto end()       { return _nodes.end();   }

    unsigned count() const { return _nodes.size(); }

    const Node & node(unsigned i) const { return _nodes.at(i); }
          Node & node(unsigned i)       { return _nodes.at(i); }

    // actions

    void refresh();

 private:
    std::vector<Node> _nodes;
    runai::Metric<Metric> _metric;
};

} // namespace runai
