#pragma once

#include <string>

#include "agent/agent/agent.h"

namespace runai::agent
{

struct SSH : Agent
{
    SSH(const std::string & hostname, const std::string & username);

 protected:
    std::string _execute(const std::string & command) override;

 private:
    std::string _hostname;
    std::string _username;
};

} // namespace runai::agent
