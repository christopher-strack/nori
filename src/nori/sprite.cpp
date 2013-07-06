#include "nori/detail/precompiled.h"
#include "nori/sprite.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <boost/algorithm/clamp.hpp>


namespace nori {

sprite::sprite(const texture_parts& slices)
    : _texture_slices(slices),
      _slice_index(0)
{
    assert(!slices.empty());

    auto slice = _texture_slices[0];
    nori::size texture_size = std::get<0>(slice)->size();
    size_f slice_size = std::get<1>(slice).size();
    _size = size_f(slice_size.x * texture_size.x, slice_size.y * texture_size.y);
}

void sprite::set_size(const size_f& size) {
    _size = size;
}

const size_f& sprite::size() const {
    return _size;
}

void sprite::set_position(const point_f& position) {
    _position = position;
}

const point_f& sprite::position() const {
    return _position;
}

int sprite::slice_count() const {
    return _texture_slices.size();
}

void sprite::set_animation(const animation& animation) {
    _animation = animation;
}

void sprite::render(renderer& renderer) {
    assert(_slice_index >= 0);
    assert(_slice_index < slice_count());

    texture_atlas_ptr texture;
    rectangle_f coords;
    tie(texture, coords) = _texture_slices[_slice_index];
    renderer.render(*texture, coords, _position, _size);
}

void sprite::update(float elapsed_seconds) {
    _animation.advance(elapsed_seconds);
    _slice_index = boost::algorithm::clamp(_animation.value(), 0, slice_count()-1);
}

} // namespace nori
