#include "nori/shader_program.h"
#include "nori/shader.h"
#include "nori/log.h"
#include "nori/matrix4.h"

#include <stdexcept>


namespace nori {

shader_attribute::shader_attribute(const std::string& name, shader_program& program)
    : _program(program), _attribute_id(-1)
{
    if (!program.is_active()) {
        throw std::runtime_error("Trying create a shader attribute at an invalid state.");
    }

    _attribute_id = ::glGetAttribLocation(program.program_id(), name.c_str());

    if (_attribute_id == -1) {
        throw std::runtime_error("Couldn't get attribute location");
    }
}

shader_attribute& shader_attribute::operator=(const vertex_buffer& vertices) {
    if (!is_valid()) {
        throw std::runtime_error("Uniform can only be changed when program is active");
    }
    if (!vertices.empty()) {
        ::glVertexAttribPointer(_attribute_id, 2, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
        ::glEnableVertexAttribArray(_attribute_id);
    }
    return *this;
}

bool shader_attribute::is_valid() const {
    return _program.is_active();
}


shader_uniform::shader_uniform(const std::string& name, shader_program& program)
    : _program(program), _uniform_id(-1)
{
    if (!program.is_active()) {
        throw std::runtime_error("Trying create a shader uniform at an invalid state.");
    }

    _uniform_id = ::glGetUniformLocation(program.program_id(), name.c_str());

    if (_uniform_id == -1) {
        throw std::runtime_error("Couldn't get uniform location");
    }
}

shader_uniform& shader_uniform::operator=(const matrix4& matrix) {
    if (!is_valid()) {
        throw std::runtime_error("Uniform can only be changed when program is active");
    }
    ::glUniformMatrix4fv(_uniform_id, 1, false, matrix.elements);
    return *this;
}

bool shader_uniform::is_valid() const {
    return _program.is_active();
}


GLuint shader_program::_active_program_id = 0;

shader_program::shader_program(
    const vertex_shader& vertex_shader,
    const fragment_shader& fragment_shader)
    : _program_id(0),
      _vertex_shader_id(vertex_shader.shader_id()),
      _fragment_shader_id(fragment_shader.shader_id()),
      attributes(*this), uniforms(*this)
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
    if (info_length > 1) {
        std::vector<GLchar> info(info_length, '\0');
        ::glGetProgramInfoLog(program_id, info_length, 0, &info[0]);
        ::glDeleteShader(program_id);
        return std::string(&info[0]);
    }
    return "";
}

} /* namespace nori */
