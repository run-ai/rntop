#pragma once

#include <memory>
#include <string>

#include "agent/type/type.h"
#include "agent/agent/agent.h"

namespace runai::agent
{

struct Factory
{
    Factory(Type type);

    std::unique_ptr<Agent> create(const std::string & hostname, const std::string & username) const;

 private:
    Type _type;
};

} // namespace runai::agent
