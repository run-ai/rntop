#pragma once

#include <string>

namespace runai::ssh
{

std::string execute(const std::string & hostname,                               const std::string & command);
std::string execute(const std::string & hostname, const std::string & username, const std::string & command);

} // namespace runai::ssh
