#include "device/device.h"

namespace runai
{

Device::Device(int index, const std::string & name, const std::string & uuid) :
    _index(index),
    _name(name),
    _uuid(uuid)
{}

int Device::index() const
{
    return _index;
}

const std::string & Device::name() const
{
    return _name;
}

const std::string & Device::uuid() const
{
    return _uuid;
}

Device::Metric Device::metric() const
{
    return _metric;
}

void Device::metric(const Metric & value)
{
    _metric = value;
}

} // namespace runai
