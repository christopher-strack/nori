#include "nori/detail/precompiled.h"
#include "nori/sprite.h"


namespace nori {

sprite::sprite(const std::string& image_file)
    : _image_file(image_file)
{
}

const std::string& sprite::image_file() const {
    return _image_file;
}


sprite_ptr make_sprite(const std::string& image_file) {
    return std::make_shared<sprite>(image_file);
}

} // namespace nori
