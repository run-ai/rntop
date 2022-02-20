#pragma once

#include <string>

#include "agent/agent/agent.h"

#include "libssh/connection/connection.h"

namespace runai::agent
{

struct libssh : Agent
{
    libssh(const std::string & hostname, const std::string & username);

 protected:
    std::string _execute(const std::string & command) override;

 private:
    runai::libssh::Connection _connection;
};

} // namespace runai::agent
