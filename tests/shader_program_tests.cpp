#include "test_shaders.h"

#include <gtest/gtest.h>
#include <nori/shader.h>
#include <nori/shader_program.h>


TEST(shader_program, construct) {
    nori::vertex_shader vertex_shader(nori::testing::vertex_shader_source);
    nori::fragment_shader fragment_shader(nori::testing::fragment_shader_source);

    nori::shader_program program(vertex_shader, fragment_shader);

    ASSERT_TRUE(program.is_valid());
}

TEST(shader_program, invalid_vertex_shader) {
    nori::vertex_shader vertex_shader("invalid shader");
    nori::fragment_shader fragment_shader(nori::testing::fragment_shader_source);

    nori::shader_program program(vertex_shader, fragment_shader);

    ASSERT_FALSE(program.is_valid());
}

TEST(shader_program, invalid_fragment_shader) {
    nori::vertex_shader vertex_shader(nori::testing::vertex_shader_source);
    nori::fragment_shader fragment_shader("invalid shader");

    nori::shader_program program(vertex_shader, fragment_shader);

    ASSERT_FALSE(program.is_valid());
}

TEST(shader_program, use) {
    nori::vertex_shader vertex_shader(nori::testing::vertex_shader_source);
    nori::fragment_shader fragment_shader(nori::testing::fragment_shader_source);

    nori::shader_program program(vertex_shader, fragment_shader);

    program.use();
}
