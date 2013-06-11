#ifndef NORI_SHADER_PROGRAM_H_
#define NORI_SHADER_PROGRAM_H_

#include "nori/detail/shader_program_fwd.h"
#include "nori/detail/opengl_fwd.h"

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


class shader_uniform {
public:
    shader_uniform(const std::string& name, shader_program& program);

    bool is_valid() const;

private:
    shader_program& _program;

    GLuint _uniform_id;
};


template<typename T>
class shader_object_map : private std::map<std::string, T> {
public:
    shader_object_map(shader_program& program)
        : _program(program)
    {
    }

    mapped_type& operator[](const key_type& key) {
        if (!_program.is_active()) {
            throw std::runtime_error(
                "Cannot access attributes when the shader is not active.");
        }

        iterator it = find(key);
        if (it == end()) {
            it = this->insert(it, value_type(key, mapped_type(key, _program)));
        }
        return it->second;
    }

private:
    shader_program& _program;
};

typedef shader_object_map<shader_attribute> shader_attribute_map;
typedef shader_object_map<shader_uniform> shader_uniform_map;


class shader_program {
public:
    shader_program(
        const vertex_shader& vertex_shader,
        const fragment_shader& fragment_shader);
    ~shader_program();

    void activate();
    bool is_active() const;

    GLuint program_id() const;

    shader_attribute_map attributes;
    shader_uniform_map uniforms;

private:
    std::string _get_program_infos(GLuint program_id);

    GLuint _program_id;
    GLuint _vertex_shader_id;
    GLuint _fragment_shader_id;

    bool _active;

    static GLuint _active_program_id;
};

} /* namespace nori */

#endif /* NORI_SHADER_PROGRAM_H_ */
