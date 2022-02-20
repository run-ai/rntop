#pragma once

#include <string>
#include <vector>

#include "agent/type/type.h"

namespace runai
{

struct Arguments
{
    std::vector<std::string> hostnames = {};
    unsigned interval = 0;
    agent::Type agent = agent::Type::libssh;
    std::string username = "";

    static Arguments parse(int argc, char * argv[]);
};

} // namespace runai
