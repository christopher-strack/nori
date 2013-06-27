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

    auto node = std::make_shared<sprite_node>(desc.texture, desc.texture_coords);
    node->set_size(desc.size);
    _sprite_nodes.push_back(node);
    return node;
}

scene::sprite_description scene::_create_sprite_description(sprite_ptr sprite) {
    sprite_description desc;
    image img(sprite->image_file());
    auto texture_part = _try_fit_image(img);
    if (!texture_part) {
        auto texture = std::make_shared<texture_atlas>();
        auto coords  = texture->add(img);
        if (coords) {
            desc.texture_coords = *coords;
            desc.texture = texture;
            _textures.push_back(texture);
        }
        else {
            throw std::runtime_error("Couldn't fit image into texture");
        }
    }
    else {
        tie(desc.texture, desc.texture_coords) = *texture_part;
    }
    desc.size = img.size();
    return desc;
}

boost::optional<std::tuple<texture_atlas_ptr, rectangle_f>>
scene::_try_fit_image(const image& image)
{
    boost::optional<std::tuple<texture_atlas_ptr, rectangle_f>> result;
    auto it = boost::find_if(_textures, [&](texture_atlas_ptr texture)->bool {
        if (auto coords = texture->add(image)) {
            result = std::make_tuple(texture, *coords);
        }
        return result;
    });
    return result;
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
