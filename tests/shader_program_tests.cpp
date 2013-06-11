#include "test_shaders.h"

#include <gtest/gtest.h>
#include <nori/shader.h>
#include <nori/shader_program.h>

#include <stdexcept>


class shader_program_fixture : public ::testing::Test {
public:
    nori::shader_program create_program() {
        return nori::shader_program(
            nori::vertex_shader(nori::testing::vertex_shader_source),
            nori::fragment_shader(nori::testing::fragment_shader_source));
    }
};


TEST_F(shader_program_fixture, construct) {
    nori::shader_program program = create_program();
}

TEST_F(shader_program_fixture, activate) {
    nori::shader_program program = create_program();

    ASSERT_FALSE(program.is_active());

    program.activate();

    ASSERT_TRUE(program.is_active());
}

TEST_F(shader_program_fixture, global_active_state) {
    nori::shader_program program1 = create_program();
    nori::shader_program program2 = create_program();

    program1.activate();

    ASSERT_TRUE(program1.is_active());
    ASSERT_FALSE(program2.is_active());

    program2.activate();

    ASSERT_FALSE(program1.is_active());
    ASSERT_TRUE(program2.is_active());
}

TEST_F(shader_program_fixture, attribute) {
    nori::shader_program program = create_program();

    program.activate();
    nori::shader_attribute& attribute = program.attributes["position"];

    ASSERT_TRUE(attribute.is_valid());
}

TEST_F(shader_program_fixture, invalid_attribute) {
    nori::shader_program program = create_program();

    program.activate();
    ASSERT_THROW(program.attributes["invalid_name"], std::runtime_error);
}

TEST_F(shader_program_fixture, invalid_program_state) {
    nori::shader_program program = create_program();

    ASSERT_THROW(program.attributes["position"], std::runtime_error);
}

TEST_F(shader_program_fixture, attribute_state) {
    nori::shader_program program1 = create_program();
    nori::shader_program program2 = create_program();

    program1.activate();
    nori::shader_attribute& attribute = program1.attributes["position"];

    ASSERT_TRUE(attribute.is_valid());

    program2.activate();

    ASSERT_FALSE(attribute.is_valid());
}
