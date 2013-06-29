#include "nori/detail/precompiled.h"
#include "nori/scene.h"
#include "nori/image.h"
#include "nori/sprite.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <memory>
#include <math.h>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/find.hpp>

using std::tie;


namespace nori {

sprite_node::sprite_node(const texture_slices& slices)
    : _texture_slices(slices), _slice_index(0)
{
    assert(!slices.empty());

    auto slice = _texture_slices[0];
    nori::size texture_size = std::get<0>(slice)->size();
    size_f slice_size = std::get<1>(slice).size();
    _size = size_f(slice_size.x * texture_size.x, slice_size.y * texture_size.y);
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

int sprite_node::slice_count() const {
    return _texture_slices.size();
}

void sprite_node::render(renderer& renderer) {
    texture_atlas_ptr texture;
    rectangle_f coords;
    tie(texture, coords) = _texture_slices[_slice_index];
    renderer.render(*texture, coords, _position, _size);
}


scene::scene() {
}

sprite_node_ptr scene::add_sprite(sprite_ptr sprite) {
    texture_slices slices;

    auto it = _sprites.find(sprite);
    if (it == _sprites.end()) {
        slices = _slice_sprite(sprite);
        _sprites.insert(sprite_map::value_type(sprite, slices));
    }
    else {
        slices = it->second;
    }

    auto node = std::make_shared<sprite_node>(slices);
    _sprite_nodes.push_back(node);
    return node;
}

texture_slices scene::_slice_sprite(sprite_ptr sprite) {
    auto slices = _try_fit_sprite(sprite);
    if (slices.empty()) {
        auto texture = std::make_shared<texture_atlas>();
        _textures.push_back(texture);
        slices = _try_fit_sprite(sprite);
        if (slices.empty()) {
            throw std::runtime_error("Couldn't fit image into texture");
        }
    }
    return slices;
}

texture_slices scene::_try_fit_sprite(const sprite_ptr& sprite) {
    texture_slices slices;
    if (!_textures.empty()) {
        image img(sprite->image_file());
        size_f grid_size;
        size_f cell_size;
        tie(grid_size, cell_size) = _slice_image(
            img, size_f(sprite->slice_size()));

        auto it = boost::find_if(_textures, [&](texture_atlas_ptr texture)->bool {
            if (auto result = texture->add(img)) {
                const rectangle_f& coords = *result;
                slices = _slice_texture_part(texture, coords, grid_size, cell_size);
            }
            return !slices.empty();
        });
    }
    return slices;
}

texture_slices scene::_slice_texture_part(
    texture_atlas_ptr texture,
    const rectangle_f& coords,
    const size_f& grid_size,
    const size_f& cell_size)
{
    texture_slices slices;
    const size_f coord_size(
        cell_size.x / texture->size().x,
        cell_size.y / texture->size().y);
    for (int y = 0; y < grid_size.y; y++) {
        for (int x = 0; x < grid_size.x; x++) {
            const point_f p(coord_size.x * x, coord_size.y * y);
            rectangle_f slice_coords(coords.position() + p, coord_size);
            slices.push_back(std::make_tuple(texture, slice_coords));
        }
    }
    return slices;
}

std::tuple<size_f, size_f>
scene::_slice_image(const image& img, const size_f& requested_size) {
    vector2<float> grid_size(1, 1);
    size_f cell_size = img.size();
    if (requested_size != size()) {
        cell_size = requested_size;
        for (int i = 0; i < 2; i++) {
            grid_size[i] = ceil(img.size()[i] / cell_size[i]);
        }
    }
    return std::make_tuple(grid_size, cell_size);
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
