#include "ssh/ssh.h"

#include <vector>

#include "popen/popen.h"
#include "utils/utils.h"

namespace runai::ssh
{

std::string execute(const std::string & hostname, const std::string & command)
{
    return execute(hostname, /* username */ "", command);
}

std::string execute(const std::string & hostname, const std::string & username, const std::string & command)
{
    auto components = std::vector<std::string> { "ssh", hostname };

    if (!username.empty())
    {
        components.push_back("-l");
        components.push_back(username);
    }

    components.push_back(command);

    return Popen::execute(utils::string::join(components, ' '));
}

} // namespace runai::ssh
