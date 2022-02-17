#pragma once

#include <ostream>
#include <string>

#include "libssh/session/session.h"

namespace runai::libssh
{

struct Key
{
    Key(const Session & session);
    ~Key();

    Key(const Key &) = delete;
    Key & operator=(const Key &) = delete;

    Key(Key &&) = delete;
    Key & operator=(Key &&) = delete;

    operator ssh_key() const { return _key; }

    struct Hash
    {
        Hash(const Key & key, ssh_publickey_hash_type type);
        ~Hash();

        Hash(const Hash &) = delete;
        Hash & operator=(const Hash &) = delete;

        Hash(Hash &&) = delete;
        Hash & operator=(Hash &&) = delete;

        operator std::string() const;

        friend std::ostream & operator<<(std::ostream & os, const Hash & hash)
        {
            return os << hash.operator std::string();
        }

     private:
        unsigned char * _hash;
        size_t _hlen;
    };

    Hash hash(ssh_publickey_hash_type type) const;
    Hash sha1() const;

 private:
    ssh_key _key;
};

} // namespace runai::libssh
