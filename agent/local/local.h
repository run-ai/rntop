#pragma once

#include <string>

#include "agent/agent/agent.h"

namespace runai::agent
{

struct Local : Agent
{
    Local(const std::string & hostname, const std::string & username);

 protected:
    std::string _execute(const std::string & command) override;
};

} // namespace runai::agent
