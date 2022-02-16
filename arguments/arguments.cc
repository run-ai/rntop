#include "arguments/arguments.h"

#include <iostream>

namespace runai
{

Arguments Arguments::parse(int argc, char * argv[])
{
    auto arguments = Arguments {};

    const auto usage = [=]()
        {
            std::cerr << "usage: " << argv[0] << " ...hostname" << std::endl;
            exit(EXIT_FAILURE);
        };

    if (argc <= 1)
    {
        usage();
    }

    for (int i = 1; i < argc; ++i)
    {
        const auto arg = std::string(argv[i]);

        if (arg == "-h" || arg == "--help")
        {
            usage();
        }
    }

    for (int i = 1; i < argc; ++i)
    {
        arguments.hostnames.push_back(argv[i]);
    }

    return arguments;
}

} // namespace runai
