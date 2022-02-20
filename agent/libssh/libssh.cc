#include "agent/libssh/libssh.h"

namespace runai::agent
{

libssh::libssh(const std::string & hostname, const std::string & username) :
    _connection(hostname, username)
{
    _connection.authenticate();
}

std::string libssh::_execute(const std::string & command)
{
    return _connection.execute(command);
}

} // namespace runai::agent
