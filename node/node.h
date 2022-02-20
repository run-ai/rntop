#pragma once

#include <memory>
#include <string>
#include <vector>

#include "agent/agent/agent.h"

namespace runai
{

struct Node
{
    Node(const std::string & hostname, std::unique_ptr<agent::Agent> && agent);

    // getters

    const std::string & hostname() const;
    const std::string & driver() const;

    // actions

    std::string execute(const std::string & command) const;

    struct Snapshot
    {
        struct Device
        {
            size_t utilization;
            size_t used_memory;
            size_t total_memory;
        };

        std::vector<Device> devices;
        size_t utilization;
        size_t used_memory;
        size_t total_memory;
    };

    Snapshot snapshot() const;

 private:
    std::string _hostname;
    std::unique_ptr<agent::Agent> _agent;
    mutable std::string _driver = {};
};

} // namespace runai
