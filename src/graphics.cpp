#include "nori/graphics.h"
#include "nori/shader.h"
#include "nori/detail/image_shader.h"

#include <boost/make_shared.hpp>


namespace nori {

graphics::graphics() {
    _image_program = boost::make_shared<shader_program>(
        vertex_shader(detail::shader_source::image_vertex),
        fragment_shader(detail::shader_source::image_fragment));

    _image_program->activate();
    shader_uniform ortho_matrix = _image_program->uniforms["ortho_matrix"];
}

void graphics::draw(image_ptr image, point position) {
    _image_program->activate();
}

} /* namespace nori */
