#include "ssh/ssh.h"

#include <utility>

#include "popen/popen.h"
#include "utils/utils.h"

namespace runai::ssh
{

std::string execute(const std::string & hostname, const std::string & command, bool strip)
{
    auto output = Popen::execute("ssh " + hostname + " " + command);

    if (strip)
    {
        output = utils::string::strip(std::move(output));
    }

    return output;
}

} // namespace runai::ssh
