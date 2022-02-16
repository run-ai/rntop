#pragma once

#include <string>
#include <vector>

namespace runai
{

struct Arguments
{
    std::vector<std::string> hostnames;

    static Arguments parse(int argc, char * argv[]);
};

} // namespace runai
