#include "nori/detail/precompiled.h"
#include "nori/sprite.h"
#include "nori/renderer.h"
#include "nori/texture_atlas.h"

#include <boost/algorithm/clamp.hpp>

namespace {

nori::animation empty_animation;

} // anonymous namespace


namespace nori {

sprite::sprite(const texture_parts& slices)
    : _texture_slices(slices),
      _slice_index(-1),
      _animation(&empty_animation),
      _scale(1.0f)
{
    assert(!slices.empty());
    _set_slice_index(_animation->value());
}

sprite& sprite::set_scale(float scale) {
    _scale = scale;
    _update_scaled_size();
    return *this;
}

const size_f& sprite::size() const {
    return _scaled_size;
}

sprite& sprite::set_position(const point_f& position) {
    _position = position;
    return *this;
}

const point_f& sprite::position() const {
    return _position;
}

int sprite::slice_count() const {
    return _texture_slices.size();
}

sprite& sprite::set_animation(animation& animation) {
    _animation = &animation;
    _set_slice_index(_animation->value());
    return *this;
}

void sprite::render(renderer& renderer) {
    assert(_slice_index >= 0);
    assert(_slice_index < slice_count());

    texture_atlas_ptr texture;
    rectangle_f coords;
    tie(texture, coords) = _texture_slices[_slice_index];
    renderer.render(*texture, coords, _position - _scaled_size / 2.0f, _scaled_size);
}

void sprite::update(float elapsed_seconds) {
    _animation->advance(elapsed_seconds);
    _set_slice_index(_animation->value());
}

void sprite::_set_slice_index(int index) {
    if (index != _slice_index) {
        _slice_index = boost::algorithm::clamp(_animation->value(), 0, slice_count()-1);
        auto slice = _texture_slices[_slice_index];
        nori::size texture_size = std::get<0>(slice)->size();
        size_f slice_size = std::get<1>(slice).size();
        _size = size_f(slice_size.x * texture_size.x, slice_size.y * texture_size.y);
        _update_scaled_size();
    }
}

void sprite::_update_scaled_size() {
    _scaled_size = _size * _scale;
}

} // namespace nori
