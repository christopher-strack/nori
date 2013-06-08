#ifndef NORI_IMAGE_H_
#define NORI_IMAGE_H_

#include "nori/vector2.h"

#include <vector>


namespace nori {

class image {
public:
    typedef std::vector<unsigned char> image_buffer;

    image(const char* filename);

    nori::size size() const;
    image_buffer data() const;

private:
    image_buffer _data;
    nori::size _size;
};

} /* namespace nori */

#endif /* NORI_IMAGE_H_ */
