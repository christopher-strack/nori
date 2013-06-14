#include "nori/renderer.h"
#include "nori/shader.h"
#include "nori/texture.h"
#include "nori/graphics_surface.h"
#include "nori/detail/basic_shader.h"
#include "nori/matrix4.h"
#include "nori/rectangle.h"

#include <boost/assign/std/vector.hpp>
#include <boost/make_shared.hpp>


namespace nori {

renderer::renderer(graphics_surface_ptr graphics_surface)
    : _graphics_surface(graphics_surface)
{
    _program = boost::make_shared<shader_program>(
        vertex_shader(detail::shader_source::basic_vertex),
        fragment_shader(detail::shader_source::basic_fragment));

    _program->activate();
    size surface_size = graphics_surface->size();
    _program->uniforms["ortho_matrix"] = matrix4::make_orthogonal(surface_size);
}

void renderer::render(texture& texture, const point_f& position, const size_f& size) {
    using namespace boost::assign;

    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    ::glEnable(GL_TEXTURE_2D);
    texture.bind();

    static vertex_buffer points;
    static vertex_buffer uvs;
    points.clear();
    uvs.clear();

    rectangle_f r(position, size);
    points += r.left, r.top, r.right, r.top, r.left, r.bottom, r.right, r.bottom;
    uvs += 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f;

    _program->attributes["position"] = points;
    _program->attributes["uv"] = uvs;

    ::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

} /* namespace nori */
