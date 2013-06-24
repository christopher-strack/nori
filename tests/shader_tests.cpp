#include "precompiled.h"
#include "test_shaders.h"

#include <gmock/gmock.h>
#include <nori/shader.h>

#include <stdexcept>


TEST(shader, vertex_shader) {
    nori::vertex_shader shader(nori::testing::vertex_shader_source);
}

TEST(shader, fragment_shader) {
    nori::fragment_shader shader(nori::testing::fragment_shader_source);
}

TEST(shader, invalid_source) {
    ASSERT_THROW(nori::vertex_shader("invalid shader"), std::runtime_error);
}
