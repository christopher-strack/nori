#ifndef NORI_GRAPHICS_H_
#define NORI_GRAPHICS_H_

#include "nori/vector2.h"
#include "nori/shader_program.h"
#include "nori/detail/image_fwd.h"


namespace nori {

class graphics {
public:
    graphics();

    void draw(image_ptr image, point position);

private:
    shader_program_ptr _image_program;
};

} /* namespace nori */

#endif /* NORI_GRAPHICS_H_ */
