#include "nori/texture_atlas.h"
#include "nori/image.h"

#include <algorithm>


namespace nori {

texture_atlas::texture_atlas()
    : texture(nori::size(max_atlas_size(), max_atlas_size())), _packer(size())
{
}

texture_atlas::texture_atlas(const nori::size& size)
    : texture(size), _packer(size)
{
}

bool texture_atlas::add(const image& image, rectangle_f& coords) {
    rectangle region;
    if (_packer.pack(image.size(), region)) {
        ::glTexSubImage2D(
            GL_TEXTURE_2D, 0,
            region.left, region.top, region.size().x, region.size().y,
            GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)&image.data()[0]);
        size_f size = texture::size();
        coords = rectangle_f(
            region.left / size.x, region.top / size.y,
            region.right / size.x, region.bottom / size.y);
        return true;
    }
    return false;
}

int texture_atlas::max_atlas_size() {
    return std::min<int>(2048, max_size());
}

} // namespace nori
