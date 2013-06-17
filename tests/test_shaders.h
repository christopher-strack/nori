#ifndef NORI_TEST_SHADERS_H_
#define NORI_TEST_SHADERS_H_


namespace nori {
namespace testing {

const char vertex_shader_source[] =
"uniform mat4 matrix; \n"
"attribute vec4 position; \n"

"void main() { \n"
"    gl_Position = position * matrix; \n"
"} \n";

const char fragment_shader_source[] =
"void main() { \n"
"    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
"} \n";

} // namespace testing
} // namespace nori

#endif // NORI_TEST_SHADERS_H_
