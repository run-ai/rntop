#pragma once

#include <string>
#include <utility>
#include <vector>

#include "node/node.h"

namespace runai
{

struct Cluster
{
    Cluster(const std::vector<std::string> & hostnames);

    // getters

    auto begin() const { return _nodes.begin(); }
    auto end()  const  { return _nodes.end();   }

    // actions

    struct Snapshot
    {
        std::vector<std::pair<Node const *, Node::Snapshot>> nodes;
        size_t utilization;
        size_t used_memory;
        size_t total_memory;
    };

    Snapshot snapshot() const;

 private:
    std::vector<Node> _nodes;
};

} // namespace runai
