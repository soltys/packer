#include <packer/Utils.hpp>
#include <packer/private/config.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
std::string read_file_into_string(const std::string &file_name)
{
    std::ifstream ifs;

    ifs.open(file_name, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open a file";
        throw std::invalid_argument("could not open the file: " + file_name);
    }
    ifs.unsetf(std::ios::skipws);

    // get its size:
    ifs.seekg(0, std::ios::end);
    const std::streampos input_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto buffer = std::string();
    buffer.reserve(input_size);
    std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(buffer));
    ifs.close();

    return buffer;
}

void get_version_string(std::ostream &out)
{
    out << "packer version " << PROJECT_VERSION << " " << PROJECT_VERSION_SHA1 << std::endl;
}
