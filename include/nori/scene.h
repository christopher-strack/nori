#ifndef NORI_SCENE_H_
#define NORI_SCENE_H_

#include "nori/rectangle.h"
#include "nori/detail/scene_fwd.h"
#include "nori/detail/sprite_fwd.h"
#include "nori/detail/texture_fwd.h"
#include "nori/detail/texture_atlas_fwd.h"

#include <vector>
#include <map>


namespace nori {

class renderer;


class sprite_node {
public:
    sprite_node(texture_ptr texture, const rectangle_f& texture_coords);

    void set_size(const size_f& size);
    const size_f& size() const;

    void set_position(const point_f& position);
    const point_f& position() const;

    texture_ptr texture() const;
    rectangle_f texture_coords() const;

private:
    size_f _size;
    point_f _position;
    texture_ptr _texture;
    rectangle_f _texture_coords;
};


class scene {
public:
    scene();

    sprite_node_ptr add_sprite(sprite_ptr sprite);
    bool remove_sprite(sprite_node_ptr sprite_node);

    void render(renderer& renderer);

private:
    struct sprite_description {
        texture_atlas_ptr texture;
        rectangle_f texture_coords;
        size_f size;
    };

    typedef std::map<sprite_ptr, sprite_description> sprite_map;
    typedef std::vector<sprite_node_ptr> sprite_node_array;

    sprite_map _sprites;
    sprite_node_array _sprite_nodes;
    texture_atlas_ptr _texture_atlas;
};

} // namespace nori

#endif // NORI_SCENE_H_
