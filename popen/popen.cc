#include "popen/popen.h"

#include <iostream>
#include <sstream>

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
    std::stringstream output;

    while (true)
    {
        char buffer[100];
        const auto n = fread(buffer, 1, sizeof(buffer), _f);

        if (n == 0)
        {
            if (feof(_f))
            {
                break;
            }
            else if (ferror(_f))
            {
                std::cerr << "Failed reading from pipe" << std::endl;
                throw std::exception();
            }
        }

        output << std::string_view(buffer, n);
    }

    return output.str();
}

std::string Popen::execute(const std::string & command)
{
    return Popen(command, "r").read();
}

} // namespace runai
