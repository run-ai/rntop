#pragma once

#include <string>
#include <vector>

#include "agent/type/type.h"
#include "unit/unit.h"

namespace runai
{

struct Arguments
{
    std::vector<std::string> hostnames = {};
    int interval = 5;
    agent::Type agent = agent::Type::libssh;
    std::string username = "";
    bool color = true;
    Unit unit = Unit::MiB;
    std::string output = "";

    // information to show about GPU
    bool gpu_index = true;
    bool gpu_name = false;
    bool gpu_uuid = false;

    static Arguments parse(int argc, char * argv[]);
};

} // namespace runai
