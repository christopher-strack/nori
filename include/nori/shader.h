#ifndef NORI_SHADER_H_
#define NORI_SHADER_H_

#include "nori/detail/opengl_fwd.h"


namespace nori {

class shader {
public:
    enum shader_type {
        vertex,
        fragment
    };

    shader(shader_type type, const char* source);

    bool is_valid() const;

    GLuint shader_id() const;

private:
    void _log_infos(GLuint shader_id);

    GLuint _shader_id;
};


class vertex_shader : public shader{
public:
    vertex_shader(const char* source);
};


class fragment_shader : public shader{
public:
    fragment_shader(const char* source);
};

} /* namespace nori */

#endif /* NORI_SHADER_H_ */
