#include "nori/shader.h"
#include "nori/log.h"

#include <vector>
#include <stdexcept>


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
            std::string shader_infos = _get_shader_infos(_shader_id);
            ::glDeleteShader(_shader_id);
            _shader_id = 0;
            throw std::runtime_error(shader_infos);
        }
        else {
            std::string shader_infos = _get_shader_infos(_shader_id);
            if (!shader_infos.empty()) {
                log_warning(shader_infos.c_str());
            }
        }
    }
}

shader::~shader() {
    ::glDeleteShader(_shader_id);
}

GLuint shader::shader_id() const {
    return _shader_id;
}

std::string shader::_get_shader_infos(GLuint shader_id) {
    GLint info_length = 0;
    ::glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
    if (info_length > 1) {
        std::vector<GLchar> info(info_length, '\0');
        ::glGetShaderInfoLog(shader_id, info_length, 0, &info[0]);
        return std::string(&info[0]);
    }
    return "";
}


vertex_shader::vertex_shader(const char* source)
    : shader(shader::vertex, source)
{
}


fragment_shader::fragment_shader(const char* source)
    : shader(shader::fragment, source)
{
}

} // namespace nori
