#pragma once

#include <string>

#include "libssh/channel/channel.h"

namespace runai::libssh
{

struct Shell : Channel
{
    Shell() = default; // empty creation

    Shell(Session & session);
    ~Shell();

    Shell(const Shell &) = delete;
    Shell & operator=(const Shell &) = delete;

    Shell(Shell &&);
    Shell & operator=(Shell &&);

    std::string execute(const std::string & command);

 private:
    void _release();
};

} // namespace runai::libssh
