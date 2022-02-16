#include <iostream>

#include "arguments/arguments.h"
#include "ssh/ssh.h"

namespace runai
{

extern "C" int main(int argc, char * argv[])
{
    const auto arguments = Arguments::parse(argc, argv);

    for (const auto & hostname : arguments.hostnames)
    {
        std::cout << hostname << ": " << ssh::execute(hostname, "nvidia-smi --query-gpu=driver_version --format=csv,noheader,nounits") << std::endl;
    }

    return EXIT_SUCCESS;
}

} // namespace runai
