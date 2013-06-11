#include "nori/shader_program.h"
#include "nori/shader.h"
#include "nori/log.h"

#include <stdexcept>


namespace nori {

shader_attribute::shader_attribute(const std::string& name, shader_program& program)
    : _program(program), _attribute_id(-1)
{
    _attribute_id = ::glGetAttribLocation(program.program_id(), name.c_str());

    if (!is_valid()) {
        throw std::runtime_error("Couldn't get attribute location");
    }
}

bool shader_attribute::is_valid() const {
    return _attribute_id != -1 && _program.is_active();
}


shader_attribute_map::shader_attribute_map(shader_program& program)
    : _program(program)
{
}

shader_attribute_map::mapped_type& shader_attribute_map::operator[](
    const key_type& key)
{
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


GLuint shader_program::_active_program_id = 0;

shader_program::shader_program(
    const vertex_shader& vertex_shader,
    const fragment_shader& fragment_shader)
    : _program_id(0),
      _vertex_shader_id(vertex_shader.shader_id()),
      _fragment_shader_id(fragment_shader.shader_id()),
      attributes(*this)
{
    _program_id = ::glCreateProgram();
    if (_program_id) {
        ::glAttachShader(_program_id, _vertex_shader_id);
        ::glAttachShader(_program_id, _fragment_shader_id);
        ::glLinkProgram(_program_id);

        GLint link_status = GL_FALSE;
        ::glGetProgramiv(_program_id, GL_LINK_STATUS, &link_status);
        if (link_status == GL_FALSE) {
            std::string program_infos = _get_program_infos(program_id());
            ::glDeleteProgram(_program_id);
            _program_id = 0;
            throw std::runtime_error(program_infos);
        }
    }
    else {
        throw std::runtime_error("Couldn't create shader program.");
    }
 }

shader_program::~shader_program() {
    ::glDetachShader(_program_id, _vertex_shader_id);
    ::glDetachShader(_program_id, _fragment_shader_id);
    ::glDeleteProgram(_program_id);
}

void shader_program::activate() {
    ::glUseProgram(_program_id);
    _active_program_id = _program_id;
}

bool shader_program::is_active() const {
    return _active_program_id == _program_id;
}

GLuint shader_program::program_id() const {
    return _program_id;
}

std::string shader_program::_get_program_infos(GLuint program_id) {
    GLint info_length = 0;
    ::glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
    std::vector<GLchar> info(info_length, '\0');
    if (info_length > 1) {
        ::glGetProgramInfoLog(program_id, info_length, 0, &info[0]);
        ::glDeleteShader(program_id);
        log_warning(&info[0]);
    }
    return &info[0];
}

} /* namespace nori */
