#include "popen/popen.h"

#include <iostream>

namespace runai
{

Popen::Popen(const std::string & command, const std::string & type) :
    _f(popen(command.c_str(), type.c_str()))
{
    if (_f == nullptr)
    {
        std::cerr << "Failed executing command '" << command << "'" << std::endl;
        throw std::exception();
    }
}

Popen::~Popen()
{
    if (_f != nullptr && pclose(_f) != 0)
    {
        std::cerr << "Something went wrong when executed command" << std::endl;
    }
}

Popen::Popen(Popen && other) :
    _f(other._f)
{
    other._f = nullptr;
}

std::string Popen::read()
{
    std::string output;

    while (true)
    {
        const auto c = fgetc(_f);

        if (feof(_f))
        {
            break;
        }

        output.push_back(c);
    }

    return output;
}

std::string Popen::execute(const std::string & command)
{
    return Popen(command, "r").read();
}

} // namespace runai
