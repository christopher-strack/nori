#ifndef NORI_GRAPHICS_H_
#define NORI_GRAPHICS_H_

#include "nori/vector2.h"
#include "nori/detail/image_fwd.h"


namespace nori {

class graphics {
public:
    void draw(image_ptr image, point position);
};

} /* namespace nori */

#endif /* NORI_GRAPHICS_H_ */
