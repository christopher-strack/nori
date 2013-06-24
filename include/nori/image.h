#ifndef NORI_IMAGE_H_
#define NORI_IMAGE_H_

#include "nori/detail/image_fwd.h"
#include "nori/vector2.h"

#include <vector>


namespace nori {

class image {
public:
    typedef std::vector<unsigned char> image_buffer;

    image(const std::string& filename);

    virtual nori::size size() const;
    virtual image_buffer data() const;

protected:
    image();

private:
    image_buffer _data;
    nori::size _size;
};

} // namespace nori

#endif // NORI_IMAGE_H_
