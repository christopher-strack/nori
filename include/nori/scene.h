#ifndef NORI_SCENE_H_
#define NORI_SCENE_H_

#include "nori/animation.h"
#include "nori/rectangle.h"
#include "nori/detail/scene_fwd.h"
#include "nori/detail/sprite_fwd.h"
#include "nori/detail/texture_fwd.h"
#include "nori/detail/texture_atlas_fwd.h"

#include <vector>
#include <map>
#include <tuple>


namespace nori {

class renderer;
class image;

typedef std::vector<std::tuple<texture_atlas_ptr, rectangle_f>> texture_slices;


class sprite_node {
public:
    sprite_node(const texture_slices& slices);

    void set_size(const size_f& size);
    const size_f& size() const;

    void set_position(const point_f& position);
    const point_f& position() const;

    int slice_count() const;

    void set_animation(const animation& animation);

    void render(renderer& renderer);
    void update(float elapsed_seconds);

private:
    size_f _size;
    point_f _position;
    texture_slices _texture_slices;
    int _slice_index;
    animation _animation;
};


class scene {
public:
    scene();

    sprite_node_ptr add_sprite(sprite_ptr sprite);
    bool remove_sprite(sprite_node_ptr sprite_node);

    void render(renderer& renderer);
    void update(float elapsed_seconds);

private:
    typedef std::map<sprite_ptr, texture_slices> sprite_map;
    typedef std::vector<sprite_node_ptr> sprite_node_array;
    typedef std::vector<texture_atlas_ptr> texture_atlas_array;

    texture_slices _slice_sprite(sprite_ptr sprite);
    texture_slices _try_fit_sprite(const sprite_ptr& sprite);
    texture_slices _slice_texture_part(
        texture_atlas_ptr texture,
        const rectangle_f& coords,
        const size_f& grid_size,
        const size_f& cell_size);
    std::tuple<size_f, size_f>
    _slice_image(const image& img, const size_f& requested_size);

    sprite_map _sprites;
    sprite_node_array _sprite_nodes;
    texture_atlas_array _textures;
};

} // namespace nori

#endif // NORI_SCENE_H_
