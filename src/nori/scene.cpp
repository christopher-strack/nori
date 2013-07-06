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


namespace nori {

scene::scene() {
}

sprite_ptr scene::add_sprite(
    const std::string& image_file,
    slicer_base& slicer)
{
    texture_parts slices = _slice_image(image_file, slicer);
    auto s = std::make_shared<sprite>(slices);
    _sprites.push_back(s);
    return s;
}

nori::sprite_ptr scene::add_sprite(const std::string& image_file) {
    default_slicer slicer;
    return add_sprite(image_file, slicer);
}

bool scene::remove_sprite(sprite_ptr sprite) {
    auto it = boost::find(_sprites, sprite);
    if (it != _sprites.end()) {
        boost::remove_erase(_sprites, sprite);
        return true;
    }
    return false;
}

void scene::render(renderer& renderer) {
    boost::for_each(_sprites, [&](sprite_ptr sprite) {
        sprite->render(renderer);
    });
}

void scene::update(float elapsed_seconds) {
    boost::for_each(_sprites, [=](sprite_ptr sprite) {
        sprite->update(elapsed_seconds);
    });
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
        return !parts.empty();
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

} // namespace nori
