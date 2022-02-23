#pragma once

#include <string>

#include "metric/metric.h"

namespace runai
{

struct Device
{
    Device(int index, const std::string & name, const std::string & uuid);

    using Metric = metric::Common<false>;

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
