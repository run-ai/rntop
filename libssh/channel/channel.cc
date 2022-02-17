#include "libssh/channel/channel.h"

#include <iostream>
#include <sstream>
#include <utility>

namespace runai::libssh
{

Channel::Channel(Session & session) :
    _channel(ssh_channel_new(session))
{
    if (_channel == nullptr)
    {
        std::cerr << "Failed creating SSH channel" << std::endl;
        throw std::exception();
    }
}

Channel::~Channel()
{
    _release();
}

Channel::Channel(Channel && other)
{
    *this = std::move(other);
}

Channel & Channel::operator=(Channel && other)
{
    _release();

    _channel = other._channel;

    other._channel = nullptr;

    return *this;
}

std::string Channel::read()
{
    std::stringstream stream;

    while (true)
    {
        char buffer[100];
        const auto bytes = ssh_channel_read(_channel, buffer, sizeof(buffer), 0);

        if (bytes > 0)
        {
            stream << std::string_view(buffer, bytes);
        }
        else // eof or closed
        {
            if (!ssh_channel_is_eof(_channel))
            {
                std::cerr << "Failed reading command output" << std::endl;
                throw std::exception();
            }

            break; // anyways we are done
        }
    }

    return stream.str();
}

void Channel::_release()
{
    if (_channel != nullptr)
    {
        ssh_channel_free(_channel);
    }
}

} // namespace runai::libssh
