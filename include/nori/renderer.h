#ifndef NORI_RENDERER_H_
#define NORI_RENDERER_H_

#include "nori/vector2.h"
#include "nori/rectangle.h"
#include "nori/shader_program.h"
#include "nori/detail/graphics_surface_fwd.h"


namespace nori {

class texture;


class renderer {
public:
    renderer(graphics_surface_ptr graphics_surface);

    virtual void render(
        texture& texture,
        const point_f& position,
        const size_f& size);
    virtual void render(
        texture& texture,
        const rectangle_f& texture_coords,
        const point_f& position,
        const size_f& size);

protected:
    renderer();

private:
    void _enable_alpha_blending();

    graphics_surface_ptr _graphics_surface;
    shader_program_ptr _program;
};

} // namespace nori

#endif // NORI_RENDERER_H_
