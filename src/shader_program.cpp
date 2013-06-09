#include "nori/shader_program.h"
#include "nori/shader.h"
#include "nori/log.h"

#include <vector>


namespace nori {

shader_program::shader_program(
    const vertex_shader& vertex_shader,
    const fragment_shader& fragment_shader)
    : _program_id(0)
{
    if (vertex_shader.is_valid() && fragment_shader.is_valid()) {
        _program_id = ::glCreateProgram();
        if (_program_id) {
            ::glAttachShader(_program_id, vertex_shader.shader_id());
            ::glAttachShader(_program_id, fragment_shader.shader_id());
            ::glLinkProgram(_program_id);

            GLint link_status = GL_FALSE;
            ::glGetProgramiv(_program_id, GL_LINK_STATUS, &link_status);
            if (link_status == GL_FALSE) {
                log_error("Could not link program.");
                _log_infos(_program_id);
                ::glDeleteProgram(_program_id);
                _program_id = 0;
            }
        }
    }
}

bool shader_program::is_valid() const {
    return _program_id != 0;
}

void shader_program::use() {
    ::glUseProgram(_program_id);
}

void shader_program::_log_infos(GLuint program)
{
    GLint info_length = 0;
    ::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length > 1) {
        std::vector<GLchar> info(info_length, '\0');
        ::glGetProgramInfoLog(program, info_length, 0, &info[0]);
        ::glDeleteShader(program);
        log_warning(&info[0]);
    }
}

} /* namespace nori */
