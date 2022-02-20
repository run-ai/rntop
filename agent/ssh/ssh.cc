#include "agent/ssh/ssh.h"

#include "ssh/ssh.h"

namespace runai::agent
{

SSH::SSH(const std::string & hostname, const std::string & username) :
    _hostname(hostname),
    _username(username)
{}

std::string SSH::_execute(const std::string & command)
{
    return ssh::execute(_hostname, _username, command);
}

} // namespace runai::agent
