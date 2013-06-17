#ifndef NORI_STL_FILE_H_
#define NORI_STL_FILE_H_

#include <fstream>


namespace nori {
namespace detail {

class stl_file {
public:
    stl_file();
    stl_file(const char* filename);
    ~stl_file();

    bool open(const char* filename);
    void close();
    bool is_open() const;

    unsigned int size();
    unsigned int read(char* buffer, unsigned int size);

private:
    std::fstream _filestream;
};

} // namespace detail
} // namespace nori

#endif /* NORI_STL_FILE_H_ */
