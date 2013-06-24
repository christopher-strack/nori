#include "precompiled.h"
#include "test_shaders.h"

#include <gmock/gmock.h>
#include <nori/shader.h>
#include <nori/shader_program.h>
#include <nori/matrix4.h>

#include <boost/assign/std/vector.hpp>

#include <stdexcept>

using namespace boost::assign;



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
}

TEST_F(shader_program_fixture, invalid_attribute) {
    nori::shader_program program = create_program();

    program.activate();
    ASSERT_THROW(program.attributes["i  nvalid_name"], std::runtime_error);
}

TEST_F(shader_program_fixture, invalid_program_state) {
    nori::shader_program program = create_program();

    ASSERT_THROW(program.attributes["position"], std::runtime_error);
    ASSERT_THROW(program.uniforms["matrix"], std::runtime_error);
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

TEST_F(shader_program_fixture, attribute_set_vertex_buffer) {
    nori::shader_program program = create_program();

    program.activate();
    nori::vertex_buffer vertices;
    vertices += 1.0f, 2.0f, 3.0f;
    program.attributes["position"] = vertices;
}

TEST_F(shader_program_fixture, attribute_set_empty_vertex_buffer) {
    nori::shader_program program = create_program();

    program.activate();
    nori::vertex_buffer vertices;
    program.attributes["position"] = vertices;
}

TEST_F(shader_program_fixture, attribute_set_verticex_buffer_invalid_state) {
    nori::shader_program program = create_program();

    nori::vertex_buffer vertices;
    vertices += 1.0f, 2.0f, 3.0f;
    ASSERT_THROW(program.attributes["position"] = vertices, std::runtime_error);
}

TEST_F(shader_program_fixture, uniform) {
    nori::shader_program program = create_program();

    program.activate();
    nori::shader_uniform& uniform= program.uniforms["matrix"];
}

TEST_F(shader_program_fixture, invalid_uniform) {
    nori::shader_program program = create_program();

    program.activate();
    ASSERT_THROW(program.uniforms["invalid_name"], std::runtime_error);
}

TEST_F(shader_program_fixture, uniform_set_matrix) {
    nori::shader_program program = create_program();

    program.activate();
    program.uniforms["matrix"] = nori::matrix4();
}

TEST_F(shader_program_fixture, uniform_set_matrix_invalid) {
    nori::shader_program program = create_program();

    ASSERT_THROW(program.uniforms["matrix"] = nori::matrix4(), std::runtime_error);
}
