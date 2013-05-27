#ifndef NORI_GRAPHICS_SURFACE_H_
#define NORI_GRAPHICS_SURFACE_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"


namespace nori {

class graphics_surface {
public:
    virtual const nori::size& size() const = 0;

    virtual void clear() = 0;
    virtual void swap() = 0;
};

} /* namespace nori */

#endif /* NORI_GRAPHICS_SURFACE_H_ */
