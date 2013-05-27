#ifndef NORI_GRAPHICS_SURFACE_H_
#define NORI_GRAPHICS_SURFACE_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"
#include "nori/detail/windows_fwd.h"


namespace nori {

class window;

class graphics_surface {
public:
    graphics_surface(HWND window_handle, const window& window);
    ~graphics_surface();

    const size& size() const;

    void clear();
    void swap();

private:
    void _initialize(const window& window);
    void _release();
    void _set_pixel_format(int bits);

    HWND _window_handle;
    HDC _device_context;
    HGLRC _opengl_context;
    nori::size _size;
};

} /* namespace nori */

#endif /* NORI_GRAPHICS_SURFACE_H_ */
