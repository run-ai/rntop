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
            std::cerr << "\nSettings:" << std::endl;
            std::cerr << "  -i --interval       Interval in seconds between updates; default: " << arguments.interval << std::endl;
            std::cerr << "  -l -u --username    Username for login" << std::endl;
            std::cerr << "  --ssh               Use 'ssh' command for remote execution" << std::endl;
            std::cerr << "  --libssh            Use libssh for remote execution (default)" << std::endl;
            std::cerr << "\nGUI:" << std::endl;
            std::cerr << "  --mb --mib --gb --gib   Unit for memory metrics" << std::endl;
            std::cerr << "  --[no-]color            Use colors; default: " << arguments.color << std::endl;
            std::cerr << "\nInformation about GPU:" << std::endl;
            std::cerr << " --[no-]gpu-index     Zero based index of the GPU; default: " << arguments.gpu_index << std::endl;
            std::cerr << " --[no-]gpu-name      The official product name of the GPU; default: " << arguments.gpu_name << std::endl;
            std::cerr << " --[no-]gpu-uuid      UUID of the GPU; default: " << arguments.gpu_uuid << std::endl;
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
                arguments.interval = std::stoi(arg);
            }
            catch (const std::exception &)
            {
                usage();
            }

            if (arguments.interval <= 0)
            {
                std::cerr << "Interval must be greater than 0" << std::endl;
                exit(EXIT_FAILURE);
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
        else if (arg == "--mb") { arguments.unit = Unit::MB; }
        else if (arg == "--mib") { arguments.unit = Unit::MiB; }
        else if (arg == "--gb") { arguments.unit = Unit::GB; }
        else if (arg == "--gib") { arguments.unit = Unit::GiB; }
        else if (arg == "--color" || arg == "--no-color")
        {
            arguments.color = arg == "--color";
        }
        else if (arg == "--gpu-index" || arg == "--no-gpu-index")
        {
            arguments.gpu_index = arg == "--gpu-index";
        }
        else if (arg == "--gpu-name" || arg == "--no-gpu-name")
        {
            arguments.gpu_name = arg == "--gpu-name";
        }
        else if (arg == "--gpu-uuid" || arg == "--no-gpu-uuid")
        {
            arguments.gpu_uuid = arg == "--gpu-uuid";
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
