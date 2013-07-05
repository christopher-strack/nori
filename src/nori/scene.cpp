#include "nori/detail/precompiled.h"
#include "nori/scene.h"
#include "nori/image.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <array>
#include <memory>
#include <math.h>

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/algorithm/clamp.hpp>

using std::tie;


namespace {

std::array<int, 1> default_range = {0};

}


namespace nori {

sprite_node::sprite_node(const texture_parts& slices)
    : _texture_slices(slices),
      _slice_index(0),
      _animation(default_range)
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

void sprite_node::set_animation(const animation& animation) {
    _animation = animation;
}

void sprite_node::render(renderer& renderer) {
    assert(_slice_index >= 0);
    assert(_slice_index < slice_count());

    texture_atlas_ptr texture;
    rectangle_f coords;
    tie(texture, coords) = _texture_slices[_slice_index];
    renderer.render(*texture, coords, _position, _size);
}

void sprite_node::update(float elapsed_seconds) {
    _animation.advance(elapsed_seconds);
    _slice_index = boost::algorithm::clamp(_animation.value(), 0, slice_count()-1);
}


scene::scene() {
}

sprite_node_ptr scene::add_sprite(
    const std::string& image_file,
    slicer_base& slicer)
{
    texture_parts slices = _slice_image(image_file, slicer);
    auto node = std::make_shared<sprite_node>(slices);
    _sprite_nodes.push_back(node);
    return node;
}

nori::sprite_node_ptr scene::add_sprite(const std::string& image_file) {
    default_slicer slicer;
    return add_sprite(image_file, slicer);
}

texture_parts scene::_slice_image(
    const std::string& image_file,
    slicer_base& slicer)
{
    image img(image_file);
    rectangle_list slices = slicer.slice(img.size());
    auto parts = _try_fit_sliced_image(img, slices);
    if (parts.empty()) {
        auto texture = std::make_shared<texture_atlas>();
        parts = _add_sliced_image(img, slices, texture);
        if (!parts.empty()) {
            _textures.push_back(texture);
        }
        else {
            throw std::runtime_error("Couldn't fit image into texture");
        }
    }
    return parts;
}

texture_parts scene::_try_fit_sliced_image(
    const image& img,
    const rectangle_list& slices)
{
    texture_parts parts;
    boost::find_if(_textures, [&](texture_atlas_ptr texture)->bool {
        parts = _add_sliced_image(img, slices, texture);
        return parts.empty();
    });
    return parts;
}

texture_parts scene::_add_sliced_image(
    const image& img,
    const rectangle_list& slices,
    texture_atlas_ptr texture)
{
    texture_parts parts;
    if (auto result = texture->add(img)) {
        const rectangle_f& coords = *result;
        boost::for_each(slices, [&](const rectangle& slice){
            rectangle_f texture_part_coords = _to_texture_coords(
                size_f(img.size()), rectangle_f(slice), coords);
            parts.push_back(std::make_tuple(texture, texture_part_coords));
        });
    }
    return parts;
}

rectangle_f scene::_to_texture_coords(
    const size_f& size,
    const rectangle_f& slice,
    const rectangle_f& texture_region)
{
    auto slice_f = rectangle_f(slice);
    size_f texture_size = texture_region.size();
    return rectangle_f(
        slice.left / size.x * texture_size.x,
        slice.top / size.y * texture_size.y,
        slice.right / size.x * texture_size.x,
        slice.bottom / size.y * texture_size.y);
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
    boost::for_each(_sprite_nodes, [&](sprite_node_ptr node) {
        node->render(renderer);
    });
}

void scene::update(float elapsed_seconds) {
    boost::for_each(_sprite_nodes, [=](sprite_node_ptr node) {
        node->update(elapsed_seconds);
    });
}

} // namespace nori
