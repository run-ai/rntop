#pragma once

#include <string>

#include "libssh/session/session.h"

namespace runai::libssh
{

struct Connection : Session
{
    Connection() = default; // empty creation

    Connection(const std::string & host, const std::string & user = {});
    ~Connection();

    Connection(const Connection &) = delete;
    Connection & operator=(const Connection &) = delete;

    Connection(Connection &&);
    Connection & operator=(Connection &&);

    // this is done out of the c'tor to keep this class RAII
    void authenticate();

 private:
    void _release();
};

} // namespace runai::libssh
