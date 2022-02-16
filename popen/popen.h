#pragma once

#include <stdio.h>

#include <string>

namespace runai
{

struct Popen
{
    Popen() = default;
    Popen(const std::string & command, const std::string & type);
    ~Popen();

    Popen(Popen && other);
    Popen & operator=(Popen &&) = delete;

    Popen(const Popen &) = delete;
    Popen & operator=(const Popen &) = delete;

    operator FILE * () { return _f; }

    std::string read();

    static std::string execute(const std::string & command);

 private:
    FILE * _f = nullptr;
};

} // namespace runai
