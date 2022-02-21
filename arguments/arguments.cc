#include "arguments/arguments.h"

#include <iostream>

namespace runai
{

Arguments Arguments::parse(int argc, char * argv[])
{
    auto arguments = Arguments {};

    const auto usage = [=]()
        {
            std::cerr << "usage: " << argv[0] << " [-i --interval secs] [-l -u --username username] [--ssh] [--libssh] ...hostname" << std::endl;
            std::cerr << "  -i --interval       Interval in seconds between updates; default: " << arguments.interval << std::endl;
            std::cerr << "  -l -u --username    Username for login" << std::endl;
            std::cerr << "  --ssh               Use 'ssh' command for remote execution" << std::endl;
            std::cerr << "  --libssh            Use libssh for remote execution (default)" << std::endl;
            exit(EXIT_FAILURE);
        };

    if (argc <= 1)
    {
        usage();
    }

    for (int i = 1; i < argc; ++i)
    {
        auto arg = std::string(argv[i]);

        const auto shift = [&]() -> std::string &
            {
                if (i + 1 >= argc) // make sure there's at least one more argument
                {
                    usage();
                }

                arg = std::string(argv[++i]);
                return arg;
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
        else if (arg == "-l" || arg == "-u" || arg == "--username")
        {
            arguments.username = shift();
        }
        else if (arg == "--ssh")
        {
            arguments.agent = decltype(arguments.agent)::SSH;
        }
        else if (arg == "--libssh")
        {
            arguments.agent = decltype(arguments.agent)::libssh;
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
