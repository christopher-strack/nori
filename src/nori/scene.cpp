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
    sprite_description desc;

    auto it = _sprites.find(sprite);
    if (it == _sprites.end()) {
        image sprite_image(sprite->image_file());
        desc.size = sprite_image.size();
        desc.texture = std::make_shared<texture_atlas>();
        bool added = false;
        std::tie(added, desc.texture_coords) = desc.texture->add(sprite_image);
        _sprites.insert(sprite_map::value_type(sprite, desc));
    }
    else {
        desc = it->second;
    }

    auto node = std::make_shared<sprite_node>(
        desc.texture, desc.texture_coords);
    node->set_size(desc.size);
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
