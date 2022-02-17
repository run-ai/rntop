#include "libssh/key/key.h"

#include <iostream>

namespace runai::libssh
{

Key::Key(const Session & session)
{
    if (ssh_get_server_publickey(session, &_key) != SSH_OK)
    {
        std::cerr << "Failed getting server public key" << std::endl;
        throw std::exception();
    }
}

Key::~Key()
{
    ssh_key_free(_key);
}

Key::Hash Key::hash(ssh_publickey_hash_type type) const
{
    return Hash(*this, type);
}

Key::Hash Key::sha1() const
{
    return hash(SSH_PUBLICKEY_HASH_SHA1);
}

Key::Hash::Hash(const Key & key, ssh_publickey_hash_type type)
{
    if (ssh_get_publickey_hash(key, type, /* out */ &_hash, /* out */ &_hlen) != 0)
    {
        std::cerr << "Failed getting public key hash" << std::endl;
        throw std::exception();
    }
}

Key::Hash::~Hash()
{
    ssh_clean_pubkey_hash(&_hash);
}

Key::Hash::operator std::string() const
{
    struct Hexa
    {
        Hexa(const Hash & hash) : _hexa(ssh_get_hexa(hash._hash, hash._hlen))
        {}

        ~Hexa()
        {
            ssh_string_free_char(_hexa);
        }

        Hexa(const Hexa &) = delete;
        Hexa & operator=(const Hexa &) = delete;

        Hexa(Hexa &&) = delete;
        Hexa & operator=(Hexa &&) = delete;

        operator std::string() const { return _hexa; }

     private:
        char * _hexa;
    };

    return Hexa(*this);
}

} // namespace runai::libssh
