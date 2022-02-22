#pragma once

#include <memory>
#include <mutex>

namespace runai
{

struct Mutex
{
    Mutex() :
        _mutex(std::make_unique<std::mutex>())
    {}

    Mutex(Mutex &&) = default;
    Mutex & operator=(Mutex &&) = default;

    Mutex(const Mutex &) = delete;
    Mutex & operator=(const Mutex &) = delete;

    using Lock = std::unique_lock<std::mutex>;

    Lock lock()
    {
        return Lock(_mutex.operator*());
    }

 private:
    std::unique_ptr<std::mutex> _mutex;
};

} // namespace runai
