#include "nori/texture.h"
#include "nori/image.h"


namespace nori {

texture::texture(const image& image)
    : _texture_id(-1)
{
    _size = image.size();
    ::glGenTextures(1, &_texture_id);
    ::glBindTexture(GL_TEXTURE_2D, _texture_id);
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)&image.data()[0]);
}

texture::~texture() {
    ::glDeleteTextures(1, &_texture_id);
}

nori::size texture::size() const {
    return _size;
}

void texture::bind() {
    ::glBindTexture(GL_TEXTURE_2D, _texture_id);
}

} /* namespace nori */
