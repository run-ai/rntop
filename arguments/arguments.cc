#include "arguments/arguments.h"

#include <iostream>

namespace runai
{

Arguments Arguments::parse(int argc, char * argv[])
{
    auto arguments = Arguments {};

    const auto usage = [=]()
        {
            std::cerr << "usage: " << argv[0] << " [-i --interval secs] ...hostname" << std::endl;
            std::cerr << "  -i --interval        Interval in seconds between updates" << std::endl;
            exit(EXIT_FAILURE);
        };

    if (argc <= 1)
    {
        usage();
    }

    for (int i = 1; i < argc; ++i)
    {
        auto arg = std::string(argv[i]);

        const auto shift = [&]()
            {
                if (i + 1 >= argc) // make sure there's at least one more argument
                {
                    usage();
                }

                arg = std::string(argv[++i]);
            };

        if (arg == "-h" || arg == "--help")
        {
            usage();
        }
        else if (arg == "-i" || arg == "--interval")
        {
            shift();

            try
            {
                arguments.interval = std::stoul(arg);
            }
            catch (const std::exception &)
            {
                usage();
            }
        }
        else if (arg.front() == '-') // unrecognized flag
        {
            usage();
        }
        else // hostname
        {
            arguments.hostnames.push_back(arg);
        }
    }

    return arguments;
}

} // namespace runai
