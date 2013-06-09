#include "nori/shader.h"
#include "nori/log.h"

#include <string>


namespace nori {

shader::shader(shader_type type, const char* source)
    : _shader_id(0)
{
    _shader_id = ::glCreateShader(
        type == vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    if (_shader_id) {
        ::glShaderSource(_shader_id, 1, &source, 0);
        ::glCompileShader(_shader_id);

        GLint compiled = GL_FALSE;
        ::glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE) {
            log_error("Could not compile shader. \n");
            _log_infos(_shader_id);
            ::glDeleteShader(_shader_id);
            _shader_id = 0;
        }
        else {
            _log_infos(_shader_id);
        }
    }
}

bool shader::is_valid() const {
    return _shader_id != 0;
}

void shader::_log_infos(GLuint shader_id) {
    GLint info_length = 0;
    ::glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length > 1) {
        std::string info(info_length, '\0');
        GLchar* gl_info = const_cast<GLchar*>(info.data());
        ::glGetShaderInfoLog(shader_id, info_length, 0, gl_info);
        log_warning(info.c_str());
    }
}

} /* namespace nori */
