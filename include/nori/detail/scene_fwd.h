#ifndef NORI_SCENE_FWD_H_
#define NORI_SCENE_FWD_H_

#include "nori/detail/texture_atlas_fwd.h"

#include <memory>
#include <vector>
#include <tuple>


namespace nori {

class scene;
typedef std::shared_ptr<scene> scene_ptr;

typedef std::vector<std::tuple<texture_atlas_ptr, rectangle_f>> texture_parts;

} // namespace nori

#endif // NORI_SCENE_FWD_H_
