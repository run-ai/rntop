#pragma once

#include <string>
#include <vector>

#include "agent/type/type.h"

namespace runai
{

struct Arguments
{
    std::vector<std::string> hostnames = {};
    int interval = 5;
    agent::Type agent = agent::Type::libssh;
    std::string username = "";
    bool color = true;

    static Arguments parse(int argc, char * argv[]);
};

} // namespace runai
