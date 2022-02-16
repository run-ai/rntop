#pragma once

#include <set>
#include <string>
#include <vector>

namespace runai::utils::string
{

std::vector<std::string> split(const std::string & str, char delimiter);
std::string strip(std::string && str, const std::set<char> & chars = { '\r', '\n' });

} // namespace runai::utils::string
