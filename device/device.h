#pragma once

#include <string>

#include "metric/metric.h"

namespace runai
{

struct Device
{
    Device(int index, const std::string & name, const std::string & uuid);

    struct Metric
    {
        size_t utilization;
        size_t used_memory;
        size_t total_memory;
    };

    // getters

    int index() const;
    const std::string & name() const;
    const std::string & uuid() const;
    Metric metric() const;

    // setters

    void metric(const Metric & value);

 private:
    int _index;
    std::string _name;
    std::string _uuid;
    runai::Metric<Metric> _metric = {};
};

} // namespace runai
