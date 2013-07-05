#ifndef NORI_SCENE_H_
#define NORI_SCENE_H_

#include "nori/animation.h"
#include "nori/rectangle.h"
#include "nori/slicer.h"
#include "nori/detail/scene_fwd.h"
#include "nori/detail/texture_fwd.h"
#include "nori/detail/texture_atlas_fwd.h"

#include <vector>
#include <map>
#include <tuple>
#include <string>


namespace nori {

class renderer;
class image;

typedef std::vector<std::tuple<texture_atlas_ptr, rectangle_f>> texture_parts;


class sprite_node {
public:
    sprite_node(const texture_parts& slices);

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
    texture_parts _texture_slices;
    int _slice_index;
    animation _animation;
};


class scene {
public:
    scene();

    sprite_node_ptr add_sprite(const std::string& image_file);
    sprite_node_ptr add_sprite(const std::string& image_file, slicer_base& slicer);
    bool remove_sprite(sprite_node_ptr sprite_node);

    void render(renderer& renderer);
    void update(float elapsed_seconds);

private:
    typedef std::vector<sprite_node_ptr> sprite_node_array;
    typedef std::vector<texture_atlas_ptr> texture_atlas_array;

    texture_parts _slice_image(
        const std::string& image_file,
        slicer_base& slicer);
    texture_parts _try_fit_sliced_image(
        const image& img,
        const rectangle_list& slices);
    texture_parts _add_sliced_image(
        const image& img,
        const rectangle_list& slices,
        texture_atlas_ptr texture);
    rectangle_f _to_texture_coords(
        const size_f& size,
        const rectangle_f& slice,
        const rectangle_f& coords);

    sprite_node_array _sprite_nodes;
    texture_atlas_array _textures;
};

} // namespace nori

#endif // NORI_SCENE_H_
