#include "nori/detail/stl_file.h"


namespace nori {
namespace detail {

stl_file::stl_file() {

}

stl_file::stl_file(const char* filename) {
    open(filename);
}

stl_file::~stl_file() {
    close();
}

bool stl_file::open(const char* filename) {
    _filestream.open(filename, std::ios::in | std::ios::binary);
    return is_open();
}

void stl_file::close() {
    _filestream.close();
}

bool stl_file::is_open() const {
    return _filestream.is_open();
}

unsigned int stl_file::size() {
    std::streampos pos = _filestream.tellg();
    _filestream.seekg(0, std::ios::end);
    unsigned int size = static_cast<unsigned int>(_filestream.tellg() - pos);
    _filestream.seekg(pos);
    return size;
}

unsigned int stl_file::read(char* buffer, unsigned int size) {
    _filestream.read(buffer, size);
    return static_cast<unsigned int>(_filestream.gcount());
}

} /* namespace detail */
} /* namespace nori */
