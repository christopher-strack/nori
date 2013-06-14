#ifndef NORI_TEXTURE_H_
#define NORI_TEXTURE_H_

#include "nori/detail/texture_fwd.h"
#include "nori/detail/image_fwd.h"
#include "nori/detail/opengl_fwd.h"


namespace nori {

class texture {
public:
    texture(const image& image);
    ~texture();

    void bind();

private:
    GLuint _texture_id;
};

} /* namespace nori */

#endif /* NORI_TEXTURE_H_ */
