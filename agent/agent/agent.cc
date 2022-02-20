#include "agent/agent/agent.h"

#include <utility>

#include "utils/utils.h"

namespace runai::agent
{

std::string Agent::execute(const std::string & command, bool strip)
{
    auto output = _execute(command);

    if (strip)
    {
        output = utils::string::strip(std::move(output));
    }

    return output;
}

} // namespace runai::agent
