#include "nori/detail/precompiled.h"
#include "nori/scene.h"
#include "nori/image.h"
#include "nori/sprite.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <memory>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find.hpp>


namespace nori {

sprite_node::sprite_node(texture_ptr texture, const rectangle_f& texture_coords)
    : _texture(texture), _texture_coords(texture_coords)
{
}

void sprite_node::set_size(const size_f& size) {
    _size = size;
}

const size_f& sprite_node::size() const {
    return _size;
}

void sprite_node::set_position(const point_f& position) {
    _position = position;
}

const point_f& sprite_node::position() const {
    return _position;
}

texture_ptr sprite_node::texture() const {
    return _texture;
}

rectangle_f sprite_node::texture_coords() const {
    return _texture_coords;
}


scene::scene() {
}

sprite_node_ptr scene::add_sprite(sprite_ptr sprite) {
    if (_texture_atlas == 0) {
        _texture_atlas = std::make_shared<texture_atlas>();
    }
    image sprite_image(sprite->image_file());
    rectangle_f texture_coords;
    _texture_atlas->add(sprite_image, texture_coords);
    auto node = std::make_shared<sprite_node>(_texture_atlas, texture_coords);
    node->set_size(sprite_image.size());
    _sprite_nodes.push_back(node);
    return node;
}

bool scene::remove_sprite(sprite_node_ptr sprite_node) {
    auto it = boost::find(_sprite_nodes, sprite_node);
    if (it != _sprite_nodes.end()) {
        boost::remove_erase(_sprite_nodes, sprite_node);
        return true;
    }
    return false;
}

void scene::render(renderer& renderer) {
    for (auto it = _sprite_nodes.begin(); it != _sprite_nodes.end(); it++) {
        auto node = *it;
        renderer.render(
            *node->texture(), node->texture_coords(),
            node->position(), node->size());
    }
}

} // namespace nori
