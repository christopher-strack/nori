#ifndef NORI_SCENE_H_
#define NORI_SCENE_H_

#include "nori/rectangle.h"
#include "nori/slicer.h"
#include "nori/sprite.h"
#include "nori/detail/scene_fwd.h"
#include "nori/detail/texture_fwd.h"
#include "nori/detail/texture_atlas_fwd.h"

#include <vector>
#include <map>
#include <tuple>
#include <string>


namespace nori {

class renderer;
class image;


class scene {
public:
    scene();

    sprite_ptr add_sprite(const std::string& image_file);
    sprite_ptr add_sprite(const std::string& image_file, slicer_base& slicer);
    bool remove_sprite(sprite_ptr sprite);

    void render(renderer& renderer);
    void update(float elapsed_seconds);

private:
    typedef std::vector<sprite_ptr> sprite_array;
    typedef std::vector<texture_atlas_ptr> texture_atlas_array;

    texture_parts _slice_image(
        const std::string& image_file,
        slicer_base& slicer);
    texture_parts _try_fit_sliced_image(
        const image& img,
        const rectangle_list& slices);
    texture_parts _add_sliced_image(
        const image& img,
        const rectangle_list& slices,
        texture_atlas_ptr texture);
    rectangle_f _to_texture_coords(
        const size_f& size,
        const rectangle_f& slice,
        const rectangle_f& coords);

    sprite_array _sprites;
    texture_atlas_array _textures;
};

} // namespace nori

#endif // NORI_SCENE_H_
