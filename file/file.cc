#include "file/file.h"

#include <iostream>
#include <utility>

namespace runai
{

File::File(const std::string & path, int flags, mode_t mode) :
    _fd(::open(path.c_str(), flags, mode))
{
    if (_fd == -1)
    {
        std::cerr << "Failed opening file at " << path << " (" << errno << ")" << std::endl;
        throw std::exception();
    }
}

File::~File()
{
    ::close(_fd);
}

off_t File::seek(off_t offset_, int whence)
{
    const auto offset = ::lseek(_fd, offset_, whence);

    if (offset == -1)
    {
        std::cerr << "Failed seeking file" << std::endl;
        throw std::exception();
    }

    return offset;
}

void File::write(std::string line, std::string end)
{
    line += std::move(end);

    write(line.c_str(), line.size());
}

void File::write(void const * const data, const size_t size)
{
    size_t pos = 0;

    while (pos < size)
    {
        const auto written = ::write(_fd, (void*)((size_t)data + pos), size - pos); // NOLINT(readability/casting)

        if (written <= -1)
        {
            if (errno == EINTR)
            {
                continue;
            }

            std::cerr << "Failed writing to fd " << _fd << " (" << errno << ")" << std::endl;
            throw std::exception();
        }

        pos += written;
    }
}

} // namespace runai
