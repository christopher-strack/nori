#include "nori/renderer.h"
#include "nori/shader.h"
#include "nori/detail/basic_shader.h"

#include <boost/make_shared.hpp>


namespace nori {

renderer::renderer() {
    _program = boost::make_shared<shader_program>(
        vertex_shader(detail::shader_source::basic_vertex),
        fragment_shader(detail::shader_source::basic_fragment));

    _program->activate();
    shader_uniform ortho_matrix = _program->uniforms["ortho_matrix"];
}

} /* namespace nori */
