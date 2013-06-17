#ifndef NORI_TEXTURE_H_
#define NORI_TEXTURE_H_

#include "nori/vector2.h"
#include "nori/detail/texture_fwd.h"
#include "nori/detail/image_fwd.h"
#include "nori/detail/opengl_fwd.h"


namespace nori {

class texture {
public:
    texture(const image& image);
    texture(const nori::size& size);
    ~texture();

    nori::size size() const;

    void bind();

    static int max_size();

private:
    nori::size _size;
    GLuint _texture_id;
};

} // namespace nori

#endif /* NORI_TEXTURE_H_ */
