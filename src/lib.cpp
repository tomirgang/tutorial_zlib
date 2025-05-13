#include "tutorial_zlib/lib.hpp"

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include <cerrno>
#include <cstring>

namespace zlib_tutorial
{
    GzWriteStream::GzWriteStream(const std::string &filename)
        : m_gz{gzopen(filename.c_str(), "wb9")} // 'w': write, 'b':binary, '9':level
    {
        if (m_gz == NULL)
        {
            throw std::runtime_error(std::strerror(errno));
        }
    }

    GzWriteStream::~GzWriteStream()
    {
        gzclose(m_gz);
    }

    GzWriteStream &GzWriteStream::operator<<(std::span<char> &data)
    {
        write(data);
        return *this;
    }

    void GzWriteStream::write(std::span<char> data)
    {
        auto bytes = std::as_bytes(data);
        auto res = gzwrite(m_gz, bytes.data(), size(bytes));
        if (res == 0)
        {
            throw std::runtime_error("Error while writing to gz file: " + std::string(gzerror(m_gz, nullptr)));
        }
    }

    std::vector<char> read_file(const std::string &filename)
    {
        std::ifstream file{filename, std::ifstream::binary};
        if (!file)
        {
            throw std::runtime_error("Error while opening file: " + filename);
        }

        file.seekg(0, file.end);
        const auto filesize = file.tellg();
        if (filesize > 1024 * 1024 * 1024)
        {
            throw std::runtime_error("File too large: " + filename);
        }

        file.seekg(0, file.beg);

        std::vector<char> data(filesize);
        file.read(data.data(), filesize);

        return data;
    }

    void pack_file(const std::string &file, const std::string &out_file)
    {
        auto data = read_file(file);

        GzWriteStream gz{out_file};

        auto data_span = std::span<char>(data.data(), data.size());
        gz << data_span;
    }
}