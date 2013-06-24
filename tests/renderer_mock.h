#ifndef NORI_RENDERER_MOCK_H_
#define NORI_RENDERER_MOCK_H_

#include <nori/renderer.h>
#include <nori/graphics_surface.h>


namespace nori {
namespace testing {

class renderer_mock : public renderer {
public:
    MOCK_METHOD3(render,
        void(
            texture& texture,
            const point_f& position, const size_f& size));

    MOCK_METHOD4(render,
        void(
            texture& texture,
            const rectangle_f& texture_coords,
            const point_f& position, const size_f& size));
};

} // namepsace testing
} // namespace nori

#endif // NORI_RENDERER_MOCK_H_
