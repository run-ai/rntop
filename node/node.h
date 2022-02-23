#pragma once

#include <memory>
#include <string>
#include <vector>

#include "agent/agent/agent.h"
#include "device/device.h"
#include "metric/metric.h"

namespace runai
{

struct Node
{
    Node(const std::string & hostname, std::unique_ptr<agent::Agent> && agent);

    using Metric = metric::Common<false>;

    // queries

    const std::string & hostname() const { return _hostname; }
    const std::string & driver()   const { return _driver;   }

    Metric metric() const { return _metric; }

    // access

    auto begin() const { return _devices.begin(); }
    auto begin()       { return _devices.begin(); }

    auto end() const { return _devices.end(); }
    auto end()       { return _devices.end(); }

    unsigned count() const { return _devices.size(); }

    const Device & device(unsigned index) const { return _devices.at(index); }
          Device & device(unsigned index)       { return _devices.at(index); }

    // actions

    // execute any command on the node using SSH
    std::string execute(const std::string & command) const;

    // query per GPU using nvidia-smi
    std::vector<std::vector<std::string>> query(const std::vector<std::string> & queries) const;

    // refresh the node metric as well as its devices
    void refresh();

 private:
    std::unique_ptr<agent::Agent> _agent;
    std::string _hostname;
    std::string _driver = "N/A";
    std::vector<Device> _devices;
    runai::Metric<Metric> _metric = {};
};

} // namespace runai
