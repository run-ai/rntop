#include "agent/local/local.h"

#include <iostream>

#include "popen/popen.h"

namespace runai::agent
{

Local::Local(const std::string & hostname, const std::string & username)
{
    if (hostname != "localhost" || username != "")
    {
        std::cerr << "Invalid agent type (local) for hostname '" << hostname << "' and username '" << username << "'" << std::endl;
        throw std::exception();
    }
}

std::string Local::_execute(const std::string & command)
{
    return Popen::execute(command);
}

} // namespace runai::agent
