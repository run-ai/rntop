#include "logger/logger.h"

#include <memory>
#include <sstream>

namespace runai
{

std::unique_ptr<Logger> __logger;

Logger::Logger(const std::string & path) :
    _file(path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
{
    if (_file.seek(0, SEEK_END) == 0)
    {
        _file.write("timestamp,node,index,utilization,memory_used,memory_total");
    }
}

void Logger::init(const std::string & path)
{
    if (!path.empty())
    {
        __logger = std::make_unique<Logger>(path);
    }
}

void Logger::log(const std::string & timestamp, const std::string & node, unsigned index, size_t utilization, double memory_used, double memory_total)
{
    if (__logger)
    {
        std::stringstream stream;

        stream << timestamp << "," << node << "," << index << "," << utilization << "," << memory_used << "," << memory_total;

        __logger->_file.write(stream.str());
    }
}

} // namespace runai
