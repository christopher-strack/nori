#ifndef NORI_SHADER_PROGRAM_H_
#define NORI_SHADER_PROGRAM_H_

#include "nori/detail/opengl_fwd.h"

#include <boost/enable_shared_from_this.hpp>

#include <vector>
#include <map>
#include <string>


namespace nori {

class vertex_shader;
class fragment_shader;
class shader_program;


class shader_attribute {
public:
    shader_attribute(const std::string& name, shader_program& program);

    bool is_valid() const;

private:
    shader_program& _program;

    GLuint _attribute_id;
};


class shader_attribute_map : private std::map<std::string, shader_attribute> {
public:
    shader_attribute_map(shader_program& program);

    mapped_type& operator[](const key_type& value);

private:
    shader_program& _program;
};


class shader_program {
public:
    shader_program(
        const vertex_shader& vertex_shader,
        const fragment_shader& fragment_shader);
    ~shader_program();

    bool is_valid() const;

    void activate();
    bool is_active() const;

    GLuint program_id() const;

    shader_attribute_map attributes;

private:
    void _log_infos(GLuint program);

    GLuint _program_id;
    GLuint _vertex_shader_id;
    GLuint _fragment_shader_id;

    bool _active;

    static GLuint _active_program_id;
};

} /* namespace nori */

#endif /* NORI_SHADER_PROGRAM_H_ */
