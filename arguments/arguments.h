#pragma once

#include <string>
#include <vector>

namespace runai
{

struct Arguments
{
    std::vector<std::string> hostnames = {};
    unsigned interval = 0;

    static Arguments parse(int argc, char * argv[]);
};

} // namespace runai
