#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <string>

namespace runai
{

struct File
{
    File(const std::string & path, int flags, mode_t mode = 0);
    ~File();

    File(const File &) = delete;
    File & operator=(const File &) = delete;

    File(File &&) = delete;
    File & operator=(File &&) = delete;

    off_t seek(off_t offset, int whence);

    void write(void const * const data, size_t size);
    void write(std::string line, std::string end = "\n");

 private:
    int _fd;
};

} // namespace runai
