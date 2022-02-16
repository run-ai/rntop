#pragma once

#include <string>
#include <vector>

namespace runai
{

struct Node
{
    Node(const std::string & hostname);

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
    mutable std::string _driver = {};
};

} // namespace runai
