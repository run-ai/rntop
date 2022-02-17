#pragma once

#include <libssh/libssh.h>

#include <string>

namespace runai::libssh
{

struct Session
{
    Session() = default; // empty creation

    Session(const std::string & host, const std::string & user = {});
    ~Session();

    Session(const Session &) = delete;
    Session & operator=(const Session &) = delete;

    Session(Session &&);
    Session & operator=(Session &&);

    operator ssh_session() const { return _session; }

    const std::string & host() const { return _host; }

    std::string_view error() const;

    std::string execute(const std::string & command);

    void option(ssh_options_e type, const std::string & value);

 private:
    void _option(ssh_options_e type, const void * value);
    void _release();

 protected:
    ssh_session _session = nullptr;
    std::string _host;
};

} // namespace runai::libssh
