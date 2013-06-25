#ifndef NORI_TEXTURE_ATLAS_H_
#define NORI_TEXTURE_ATLAS_H_

#include "nori/texture.h"
#include "nori/rectangle.h"
#include "nori/vector2.h"
#include "nori/detail/rectangle_packer.h"
#include "nori/detail/texture_atlas_fwd.h"

#include <tuple>


namespace nori {

class image;

class texture_atlas : public texture {
public:
    texture_atlas();
    texture_atlas(const nori::size& size);

    std::tuple<bool, rectangle_f> add(const image& image);

    static int max_atlas_size();

private:
    detail::rectangle_packer _packer;
};

} // namespace nori

#endif // NORI_TEXTURE_ATLAS_H_
