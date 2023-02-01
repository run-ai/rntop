#include "agent/factory/factory.h"

#include <iostream>

#include "agent/libssh/libssh.h"
#include "agent/local/local.h"
#include "agent/ssh/ssh.h"

namespace runai::agent
{

Factory::Factory(Type type) :
    _type(type)
{}

std::unique_ptr<Agent> Factory::create(const std::string & hostname, const std::string & username) const
{
    if (_type == Type::SSH)
    {
        return std::make_unique<SSH>(hostname, username);
    }
    else if (_type == Type::libssh)
    {
        return std::make_unique<libssh>(hostname, username);
    }
    else if (_type == Type::Local)
    {
        return std::make_unique<Local>(hostname, username);
    }

    std::cerr << "Invalid agent type (" << static_cast<int>(_type) << ")" << std::endl;
    throw std::exception();
}

} // namespace runai::agent
