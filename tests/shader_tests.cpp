#include "test_shaders.h"

#include <gtest/gtest.h>
#include <nori/shader.h>


TEST(shader, vertex_shader) {
    nori::vertex_shader shader(nori::testing::vertex_shader_source);

    ASSERT_TRUE(shader.is_valid());
}

TEST(shader, fragment_shader) {
    nori::fragment_shader shader(nori::testing::fragment_shader_source);

    ASSERT_TRUE(shader.is_valid());
}

TEST(shader, invalid_source) {
    nori::vertex_shader shader("invalid shader");

    ASSERT_FALSE(shader.is_valid());
}
