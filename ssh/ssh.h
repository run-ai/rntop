#pragma once

#include <string>

namespace runai::ssh
{

std::string execute(const std::string & hostname, const std::string & command, bool strip = true);

} // namespace runai::ssh
