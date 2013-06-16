#include "nori/texture.h"
#include "nori/image.h"

#include <stdexcept>


namespace nori {

texture::texture(const image& image)
    : _texture_id(-1)
{
    _size = image.size();
    ::glGenTextures(1, &_texture_id);
    bind();
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)&image.data()[0]);
}

texture::texture(const nori::size& size)
    : _texture_id(-1)
{
    int max = max_size();
    if (size.x > max || size.y > max) {
        throw std::runtime_error("Texture size too big.");
    }
    _size = size;
    image::image_buffer empty;
    empty.resize(size.x * size.y * 4);
    ::glGenTextures(1, &_texture_id);
    bind();
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)&empty.data()[0]);
}

texture::~texture() {
    ::glDeleteTextures(1, &_texture_id);
}

nori::size texture::size() const {
    return _size;
}

int texture::max_size() {
    GLint max_texture_size;
    ::glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
    return max_texture_size;
}

void texture::bind() {
    if (_texture_id == -1) {
        throw std::runtime_error("Trying to bind an invalid texture");
    }
    ::glBindTexture(GL_TEXTURE_2D, _texture_id);
}

} /* namespace nori */
