#pragma once

#include <string>

namespace runai::agent
{

struct Agent
{
    virtual ~Agent() = default; // mark as polymorphoc

    std::string execute(const std::string & command, bool strip = true);

 protected:
    virtual std::string _execute(const std::string & command) = 0;
};

} // namespace runai::agent
