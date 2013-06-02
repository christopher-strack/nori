#ifndef NORI_ANDROID_GRAPHICS_SURFACE_H_
#define NORI_ANDROID_GRAPHICS_SURFACE_H_

#include "nori/vector2.h"
#include "nori/graphics_surface.h"
#include "nori/detail/opengl_fwd.h"


struct ANativeWindow;


namespace nori {
namespace detail {

class android_graphics_surface : public graphics_surface {
public:
    android_graphics_surface(ANativeWindow* window);
    ~android_graphics_surface();

    virtual const nori::size& size() const;

    virtual void clear();
    virtual void swap();

private:
    nori::size _size;

    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;
};

} /* namespace detail */
} /* namespace nori */

#endif /* NORI_ANDROID_GRAPHICS_SURFACE_H_ */
