#include "libssh/connection/connection.h"

#include <iostream>
#include <utility>

#include "libssh/key/key.h"

namespace runai::libssh
{

Connection::Connection(const std::string & host, const std::string & user) : Session(host, user)
{
    if (ssh_connect(_session) != SSH_OK)
    {
        std::cerr << "Failed connecting SSH session to " << _host << ": " << error() << std::endl;
        throw std::exception();
    }
}

Connection::~Connection()
{
    _release();
}

Connection::Connection(Connection && other)
{
    *this = std::move(other);
}

Connection & Connection::operator=(Connection && other)
{
    _release();
    Session::operator=(std::move(other));
    return *this;
}

void Connection::authenticate()
{
    // this was taken almost as-is from https://api.libssh.org/stable/libssh_tutor_guided_tour.html

    //
    // first of all verify the server identity
    //

    const auto sha1 = [this]()
        {
            return Key(*this).sha1();
        };

    const auto trust = []()
        {
            std::string answer;
            std::cin >> answer;

            return answer == "y";
        };

    switch (ssh_session_is_known_server(_session))
    {
        case SSH_KNOWN_HOSTS_OK:
            break;

        case SSH_KNOWN_HOSTS_CHANGED:
            std::cerr << "Host key for server changed; it is now:\n"
                << sha1() << "\n"
                << "For security reasons, connection will be stopped"
                << std::endl;
            throw std::exception();

        case SSH_KNOWN_HOSTS_OTHER:
            std::cerr << "The host key for this server was not found but "
                << "an other type of key exists.\n"
                << "An attacker might change the default server key to "
                << "confuse your client into thinking the key does not exist"
                << std::endl;
            throw std::exception();

        case SSH_KNOWN_HOSTS_NOT_FOUND:
            std::cerr << "Could not find known host file.\n"
                << "If you accept the host key here, the file will be "
                << "automatically created"
                << std::endl;

            // fall through to SSH_KNOWN_HOSTS_UNKNOWN behavior

        case SSH_KNOWN_HOSTS_UNKNOWN:
            std::cerr << "The server is unknown:\n"
                << sha1() << "\n"
                << "Do you trust the host key? (y/n)"
                << std::endl;

            if (!trust())
            {
                throw std::exception();
            }

            if (ssh_session_update_known_hosts(_session) != SSH_OK)
            {
                std::cerr << "Failed updating SSH known hosts file" << std::endl;
                throw std::exception();
            }

            break;

        case SSH_KNOWN_HOSTS_ERROR:
            std::cerr << "Failed verifying remote host: " << error() << std::endl;
            throw std::exception();
    }

    //
    // now authenticate ourselves using public/private key
    //

    // TODO(raz): support connecting with password using 'ssh_userauth_password'

    if (ssh_userauth_publickey_auto(_session, /* username */ nullptr, /* passphrase */ nullptr) != SSH_AUTH_SUCCESS)
    {
        std::cerr << "Error authenticating client side: " << error() << std::endl;
        throw std::exception();
    }
}

void Connection::_release()
{
    if (_session != nullptr)
    {
        ssh_disconnect(_session);
    }
}

} // namespace runai::libssh
