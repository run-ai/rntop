#include "libssh/session/session.h"

#include <iostream>
#include <utility>

#include "libssh/shell/shell.h"

namespace runai::libssh
{

Session::Session(const std::string & host, const std::string & user) :
    _session(ssh_new()),
    _host(host)
{
    if (_session == nullptr)
    {
        std::cerr << "Failed creating SSH session" << std::endl;
        throw std::exception();
    }

    option(SSH_OPTIONS_HOST, host);

    if (!user.empty())
    {
        option(SSH_OPTIONS_USER, user);
    }

    // TODO(raz): support setting option 'SSH_OPTIONS_LOG_VERBOSITY' configured with an environment variable
}

Session::~Session()
{
    _release();
}

Session::Session(Session && other)
{
    *this = std::move(other);
}

Session & Session::operator=(Session && other)
{
    _release();

    _session = other._session;
    _host = other._host;

    other._session = nullptr;

    return *this;
}

std::string_view Session::error() const
{
    return ssh_get_error(_session);
}

std::string Session::execute(const std::string & command)
{
    return Shell(*this).execute(command);
}

void Session::option(ssh_options_e type, const std::string & value)
{
    _option(type, reinterpret_cast<const void *>(value.c_str()));
}

void Session::_option(ssh_options_e type, const void * value)
{
    if (ssh_options_set(_session, type, value) != SSH_OK)
    {
        std::cerr << "Failed setting SSH session option" << std::endl;
        throw std::exception();
    }
}

void Session::_release()
{
    if (_session != nullptr)
    {
        ssh_free(_session);
    }
}

} // namespace runai::libssh
