#ifndef NORI_SHADER_PROGRAM_H_
#define NORI_SHADER_PROGRAM_H_

#include "nori/detail/opengl_fwd.h"


namespace nori {

class vertex_shader;
class fragment_shader;


class shader_program {
public:
    shader_program(
        const vertex_shader& vertex_shader,
        const fragment_shader& fragment_shader);

    bool is_valid() const;

    void use();

private:
    void shader_program::_log_infos(GLuint program);

    GLuint _program_id;
};

} /* namespace nori */

#endif /* NORI_SHADER_PROGRAM_H_ */
