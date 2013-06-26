#include "nori/detail/precompiled.h"
#include "nori/scene.h"
#include "nori/image.h"
#include "nori/sprite.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <memory>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/find.hpp>

using std::tie;


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

void sprite_node::render(renderer& renderer) {
    renderer.render(*_texture, _texture_coords, _position, _size);
}


scene::scene() {
}

sprite_node_ptr scene::add_sprite(sprite_ptr sprite) {
    sprite_description desc;

    auto it = _sprites.find(sprite);
    if (it == _sprites.end()) {
        desc = _create_sprite_description(sprite);
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

scene::sprite_description scene::_create_sprite_description(sprite_ptr sprite) {
    sprite_description desc;
    image img(sprite->image_file());
    bool added = false;
    tie(added, desc.texture, desc.texture_coords) = _try_fit_image(img);
    if (!added) {
        auto texture = std::make_shared<texture_atlas>();
        tie(added, desc.texture_coords) = texture->add(img);
        if (added) {
            desc.texture = texture;
            _textures.push_back(texture);
        }
        else {
            throw std::runtime_error("Couldn't fit image into texture");
        }
    }
    desc.size = img.size();
    return desc;
}

std::tuple<bool, texture_atlas_ptr, rectangle_f> scene::_try_fit_image(
    const image& image)
{
    texture_atlas_ptr texture;
    rectangle_f coords;
    auto it = boost::find_if(_textures, [&](texture_atlas_ptr t)->bool {
        texture = t;
        bool added = false;
        tie(added, coords) = texture->add(image);
        return added;
    });
    return std::make_tuple(it != _textures.end(), texture, coords);
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
        node->render(renderer);
    }
}

} // namespace nori
