#include <gtest/gtest.h>
#include <nori/shader.h>


const char vertex_shader_source[] =
    "attribute vec4 position; \n"

    "void main() { \n"
    "    gl_Position = position; \n"
    "} \n";

const char fragment_shader_source[] =
    "void main() { \n"
    "    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
    "} \n";


TEST(shader, vertex_shader) {
    nori::shader shader(nori::shader::vertex, vertex_shader_source);

    ASSERT_TRUE(shader.is_valid());
}

TEST(shader, fragment_shader) {
    nori::shader shader(nori::shader::fragment, fragment_shader_source);

    ASSERT_TRUE(shader.is_valid());
}

TEST(shader, invalid_source) {
    nori::shader shader(nori::shader::vertex, "invalid shader");

    ASSERT_FALSE(shader.is_valid());
}
