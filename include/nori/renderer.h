#ifndef NORI_RENDERER_H_
#define NORI_RENDERER_H_

#include "nori/vector2.h"
#include "nori/shader_program.h"
#include "nori/detail/image_fwd.h"


namespace nori {

class renderer {
public:
    renderer();

private:
    shader_program_ptr _program;
};

} /* namespace nori */

#endif /* NORI_RENDERER_H_ */
