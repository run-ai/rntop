#pragma once

#include <string>

#include "file/file.h"

namespace runai
{

struct Logger
{
    Logger(const std::string & path);

    static void init(const std::string & path);
    static void log(const std::string & timestamp, const std::string & node, unsigned index, size_t utilization, double memory_used, double memory_total);

 private:
    File _file;
};

} // namespace runai
