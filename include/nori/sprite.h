#ifndef NORI_SPRITE_H_
#define NORI_SPRITE_H_

#include "nori/animation.h"
#include "nori/rectangle.h"
#include "nori/detail/sprite_fwd.h"
#include "nori/detail/scene_fwd.h"


namespace nori {

class animation;
class renderer;


class sprite {
public:
    sprite(const texture_parts& slices);

    sprite& set_scale(float scale);
    const size_f& size() const;

    sprite& set_position(const point_f& position);
    const point_f& position() const;

    int slice_count() const;

    sprite& set_animation(animation& animation);

    void render(renderer& renderer);
    void update(float elapsed_seconds);

private:
    void _set_slice_index(int index);
    void _update_scaled_size();

    size_f _size;
    size_f _scaled_size;
    float _scale;
    point_f _position;
    texture_parts _texture_slices;
    int _slice_index;
    animation* _animation;
};

} // namespace nori

#endif // NORI_SPRITE_H_
