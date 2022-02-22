#pragma once

#include <functional>
#include <thread>

namespace runai
{

struct Thread
{
    Thread(const std::function<void()> & f, unsigned interval = 0);
    ~Thread(); // joins the thread

    Thread(const Thread &) = delete;
    Thread & operator=(const Thread &) = delete;

    Thread(Thread &&) = default;
    Thread & operator=(Thread &&) = delete;

    void join();

 private:
    std::thread _t;
};

} // namespace runai
