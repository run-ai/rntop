#include "utils/utils.h"

#include <sstream>
#include <utility>

namespace runai::utils::string
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
    while (chars.count(str.back()))
    {
        str.pop_back();
    }

    return std::move(str);
}

} // namespace runai::utils::string
