#include "tutorial_zlib/version.hpp"
#include "tutorial_zlib/lib.hpp"

#include <cxxopts.hpp>

#include <iostream>
#include <vector>
#include <tuple>
#include <format>

int main(int argc, char *argv[])
{

    cxxopts::Options options(
        std::format("zlib Tutorial {}", PROJECT_VERSION),
        "A small C++ program using zlib to compress a small file.");

    options.add_options()("file", "Input file name", cxxopts::value<std::string>())("o,out", "Output file name", cxxopts::value<std::string>())("h,help", "Print usage");
    options.parse_positional({"file"});

    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::string file;
    std::string out;

    try
    {
        file = result["file"].as<std::string>();
        if (result.count("out"))
        {
            out = result["out"].as<std::string>();
        }
        else
        {
            out = file + ".gz";
        }
    }
    catch (const cxxopts::exceptions::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl
                  << std::endl;
        std::cerr << options.help() << std::endl;
        return 1;
    }

    try
    {
        std::cout << "Compressing file " << file << " as " << out << std::endl;
        zlib_tutorial::pack_file(file, out);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
