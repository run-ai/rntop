#include "thread/thread.h"

#include <unistd.h>

namespace runai
{

Thread::Thread(const std::function<void()> & f, unsigned interval) :
    _t([=]()
        {
            while (true)
            {
                f();

                if (interval == 0)
                {
                    break;
                }

                sleep(interval);
            }
        })
{}

Thread::~Thread()
{
    join();
}

void Thread::join()
{
    if (_t.joinable())
    {
        _t.join();
    }
}

} // namespace runai
