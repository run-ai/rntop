#include "node/node.h"

#include <iostream>
#include <utility>

#include "ssh/ssh.h"
#include "utils/utils.h"

namespace runai
{

Node::Node(const std::string & hostname, std::unique_ptr<agent::Agent> && agent) :
    _hostname(hostname),
    _agent(std::move(agent))
{}

std::string Node::execute(const std::string & command) const
{
    return _agent->execute(command);
}

const std::string & Node::hostname() const
{
    return _hostname;
}

const std::string & Node::driver() const
{
    if (_driver.empty())
    {
        _driver = execute("nvidia-smi --query-gpu=driver_version --format=csv,noheader,nounits");

        // the output returns the same driver version for every available GPU;
        // we therefore take only the first line.
        const auto pos = _driver.find('\n');

        if (pos != std::string::npos)
        {
            _driver = _driver.substr(0, pos);
        }
    }

    return _driver;
}

Node::Snapshot Node::snapshot() const
{
    decltype(Snapshot::devices) devices_;

    for (const auto & row : utils::string::split(execute("nvidia-smi --query-gpu=utilization.gpu,memory.used,memory.total --format=csv,noheader,nounits"), '\n'))
    {
        const auto values = utils::string::split(row, ',');

        if (values.size() != 3)
        {
            std::cerr << "Failed parsing nvidia-smi output" << std::endl;
            throw std::exception();
        }

        devices_.push_back(
            {
                .utilization  = std::stoull(values.at(0)),
                .used_memory  = std::stoull(values.at(1)),
                .total_memory = std::stoull(values.at(2)),
            });
    }

    using Op = utils::Op<size_t, decltype(devices_)::value_type>;

    return Snapshot
        {
            .devices      = devices_,
            .utilization  = utils::avg(devices_, (Op)[](const auto & device){ return device.utilization;  }),
            .used_memory  = utils::sum(devices_, (Op)[](const auto & device){ return device.used_memory;  }),
            .total_memory = utils::sum(devices_, (Op)[](const auto & device){ return device.total_memory; }),
        };
}

} // namespace runai
