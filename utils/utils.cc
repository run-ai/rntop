#include "utils/utils.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace runai::utils
{

namespace string
{

std::string join(const std::vector<std::string> & elements, char delimiter)
{
    std::stringstream stream;

    const auto count = static_cast<signed int>(elements.size());

    for (int i = 0; i < count; ++i)
    {
        stream << elements.at(i);

        if (i < count - 1)
        {
            stream << delimiter;
        }
    }

    return stream.str();
}

std::vector<std::string> split(const std::string & str, char delimiter)
{
    std::vector<std::string> elements;
    std::stringstream stream(str);

    std::string element;
    while (std::getline(stream, /* out */ element, delimiter))
    {
        elements.push_back(element);
    }

    return elements;
}

std::string strip(std::string && str, const std::set<char> & chars)
{
    while (chars.count(str.front()))
    {
        str.erase(str.begin());
    }

    while (chars.count(str.back()))
    {
        str.pop_back();
    }

    return std::move(str);
}

} // namespace string

namespace unit
{

std::string symbol(Unit unit)
{
    if      (unit == Unit::MB)  { return "MB";  }
    else if (unit == Unit::MiB) { return "MiB"; }
    else if (unit == Unit::GB)  { return "GB";  }
    else if (unit == Unit::GiB) { return "GiB"; }

    std::cerr << "Invalid unit type (" << static_cast<int>(unit) << ")" << std::endl;
    throw std::exception();
}

double convert(double x, Unit from, Unit to)
{
    if (from == to)
    {
        return x;
    }

    return bytes_to(to_bytes(x, from), to);
}

size_t to_bytes(double x, Unit from)
{
    if      (from == Unit::MB)  { return x * 1000000ull; }
    else if (from == Unit::MiB) { return x * 1048576ull; }
    else if (from == Unit::GB)  { return x * 1000000000ull; }
    else if (from == Unit::GiB) { return x * 1073741824ull; }

    std::cerr << "Cannot convert " << symbol(from) << " to bytes" << std::endl;
    throw std::exception();
}

double bytes_to(size_t x, Unit to)
{
    if      (to == Unit::MB)  { return static_cast<double>(x) / 1000000ull; }
    else if (to == Unit::MiB) { return static_cast<double>(x) / 1048576ull; }
    else if (to == Unit::GB)  { return static_cast<double>(x) / 1000000000ull; }
    else if (to == Unit::GiB) { return static_cast<double>(x) / 1073741824ull; }

    std::cerr << "Cannot convert bytes to " << symbol(to) << std::endl;
    throw std::exception();
}

} // namespace unit

} // namespace runai::utils
