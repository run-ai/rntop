#pragma once

#include "mutex/mutex.h"

namespace runai
{

template <typename T>
struct Metric
{
    void store(const T & data)
    {
        const auto lock = _mutex.lock();

        _data = data;
    }

    T load() const
    {
        const auto lock = _mutex.lock();

        return _data;
    }

    operator T() const
    {
        return load();
    }

    void operator=(const T & data)
    {
        store(data);
    }

 private:
    mutable Mutex _mutex;
    T _data = {};
};

} // namespace runai
