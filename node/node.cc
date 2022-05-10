#include "node/node.h"

#include <string>
#include <utility>

#include "logger/logger.h"
#include "utils/utils.h"

namespace runai
{

Node::Node(const std::string & hostname, std::unique_ptr<agent::Agent> && agent, const Config & config) :
    _config(config),
    _agent(std::move(agent)),
    _hostname(hostname)
{
    // retrieve initial information about the node such as the
    // driver version and some information about its devices

    for (const auto & values : query({ "driver_version", "index", "name", "uuid" }))
    {
        // overwriting '_driver' is fine because the same driver
        // version is returned for every available GPU
        _driver = values.at(0);

        _devices.push_back(
            {
                .index = std::stoi(values.at(1)),
                .name  = values.at(2),
                .uuid  = values.at(3),
            });
    }
}

std::string Node::execute(const std::string & command) const
{
    return _agent->execute(command);
}

std::vector<std::vector<std::string>> Node::query(const std::vector<std::string> & queries) const
{
    auto result = std::vector<std::vector<std::string>> {};

    for (const auto & row : utils::string::split(execute("nvidia-smi --format=csv,noheader,nounits --query-gpu=" + utils::string::join(queries, ',')), '\n'))
    {
        auto values = utils::string::split(row, ',');

        for (auto & value : values)
        {
            value = utils::string::strip(std::move(value));
        }

        result.push_back(values);
    }

    return result;
}

void Node::refresh()
{
    const auto log = _log();

    auto metrics = std::vector<Device::Metric>();

    const auto rows = query({ "timestamp", "utilization.gpu", "memory.used", "memory.total" });

    for (unsigned index = 0; index < rows.size(); ++index)
    {
        const auto & row = rows.at(index);

        const auto timestamp = row.at(0); // YYYY/MM/DD HH:MM:SS.msec

        const auto metric = Device::Metric
            {
                .utilization  = std::stoull(row.at(1)),
                .used_memory  = std::stod(row.at(2)),
                .total_memory = std::stod(row.at(3)),
                .unit         = Unit::MiB,
            };

        if (log) // log metric to file if needed
        {
            Logger::log(timestamp, hostname(), index, metric.utilization, metric.used_memory, metric.total_memory);
        }

        // store device metric
        device(index).metric(metric);

        // keep for agregate information
        metrics.push_back(metric);
    }

    // calculate and store node metric

    _metric.store(
        {
            .utilization  = utils::avg(metrics, (utils::Op<size_t, Device::Metric>)[](const auto & metric){ return metric.utilization;  }),
            .used_memory  = utils::sum(metrics, (utils::Op<double, Device::Metric>)[](const auto & metric){ return metric.used_memory;  }),
            .total_memory = utils::sum(metrics, (utils::Op<double, Device::Metric>)[](const auto & metric){ return metric.total_memory; }),
            .unit         = Unit::MiB,
        });
}

bool Node::_log()
{
    if (_refreshes++ % _config.output_every == 0)
    {
        _refreshes = 1;
        return true;
    }

    return false;
}

} // namespace runai
