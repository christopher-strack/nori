#ifndef NORI_BASIC_SHADER_H_
#define NORI_BASIC_SHADER_H_


namespace nori {
namespace detail {
namespace shader_source {

const char basic_vertex[] =
    "uniform mat4 ortho_matrix; \n"

    "attribute vec4 position; \n"
    "attribute vec2 uv; \n"

    "varying vec2 v_uv; \n"

    "void main() { \n"
    "    v_uv = uv; \n"
    "    gl_Position = position * ortho_matrix; \n"
    "} \n";

const char basic_fragment[] =
    "#ifdef GL_ES \n"
    "precision mediump float; \n"
    "#endif \n"

    "varying vec2 v_uv; \n"
    "uniform sampler2D sampler; \n"

    "void main() { \n"
    "    vec4 color = texture2D(sampler, v_uv); \n"
    "    gl_FragColor = color.aaaa * color; \n"
    "} \n";

} /* namespace shader_source */
} // namespace detail
} // namespace nori

#endif // NORI_BASIC_SHADER_H_
