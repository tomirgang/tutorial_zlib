#pragma once

#include <string>
#include <vector>
#include <span>

#include <zlib.h>

namespace zlib_tutorial
{
    class GzWriteStream
    {
    public:
        explicit GzWriteStream(const std::string &filename);

        ~GzWriteStream();

        GzWriteStream &operator<<(std::span<char> &data);

    private:
        gzFile m_gz;

        void write(std::span<char> data);

        GzWriteStream(const GzWriteStream &) = delete;
        GzWriteStream &operator=(const GzWriteStream &) = delete;
    };

    std::vector<char> read_file(const std::string &filename);

    void pack_file(const std::string &file, const std::string &out_file);
}
