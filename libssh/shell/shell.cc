#include "libssh/shell/shell.h"

#include <iostream>
#include <utility>

namespace runai::libssh
{

Shell::Shell(Session & session) : Channel(session)
{
    if (ssh_channel_open_session(_channel) != SSH_OK)
    {
        std::cerr << "Failed opening SSH shell to " << session.host() << ": " << session.error() << std::endl;
        throw std::exception();
    }
}

Shell::~Shell()
{
    _release();
}

Shell::Shell(Shell && other)
{
    *this = std::move(other);
}

Shell & Shell::operator=(Shell && other)
{
    _release();
    Channel::operator=(std::move(other));
    return *this;
}

std::string Shell::execute(const std::string & command)
{
    if (ssh_channel_request_exec(_channel, command.c_str()) != SSH_OK)
    {
        std::cerr << "Failed executing command '" << command << "'" << std::endl;
        throw std::exception();
    }

    return read();
}

void Shell::_release()
{
    if (_channel != nullptr)
    {
        ssh_channel_close(_channel);
    }
}

} // namespace runai::libssh
