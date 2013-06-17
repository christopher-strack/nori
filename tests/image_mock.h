#ifndef NORI_IMAGE_MOCK_H_
#define NORI_IMAGE_MOCK_H_

#include <nori/image.h>


namespace nori {
namespace testing {

class mock_image : public nori::image {
public:
    mock_image(const nori::size& size)
        : _size(size)
    {
        _data.resize(size.x * size.y * 4);
    }

    virtual nori::size size() const {
        return _size;
    }

    virtual nori::image::image_buffer data() const {
        return _data;
    }

private:
    nori::image::image_buffer _data;
    nori::size _size;
};

} // namespace testing
} // namespace nori

#endif // NORI_IMAGE_MOCK_H_
