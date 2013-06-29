#include "nori/detail/precompiled.h"
#include "nori/sprite.h"


namespace nori {

sprite::sprite(const std::string& image_file)
    : _image_file(image_file)
{
}

sprite::sprite(const std::string& image_file, const size& slice_size)
    : _image_file(image_file), _slice_size(slice_size)
{
}

const std::string& sprite::image_file() const {
    return _image_file;
}

const size sprite::slice_size() const {
    return _slice_size;
}


sprite_ptr make_sprite(const std::string& image_file) {
    return std::make_shared<sprite>(image_file);
}

nori::sprite_ptr make_sprite(const std::string& image_file, const size& slice_size) {
    return std::make_shared<sprite>(image_file, slice_size);
}

} // namespace nori
