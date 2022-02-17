#pragma once

#include <string>

#include "libssh/session/session.h"

namespace runai::libssh
{

struct Channel
{
    Channel() = default; // empty creation

    Channel(Session & session);
    ~Channel();

    Channel(const Channel &) = delete;
    Channel & operator=(const Channel &) = delete;

    Channel(Channel &&);
    Channel & operator=(Channel &&);

    operator ssh_channel() const { return _channel; }

    std::string read();

 private:
    void _release();

 protected:
    ssh_channel _channel = nullptr;
};

} // namespace runai::libssh
