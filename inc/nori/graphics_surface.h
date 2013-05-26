#ifndef NORI_GRAPHICS_SURFACE_H_
#define NORI_GRAPHICS_SURFACE_H_

#include "nori/detail/graphics_surface_fwd.h"
#include "nori/detail/windows_fwd.h"


namespace nori {

class window;

class graphics_surface {
public:
    graphics_surface(const window& window);
    ~graphics_surface();

private:
    void _initialize(const window& window);
    void _release();
    void _set_pixel_format(int bits);

    HWND _window_handle;
    HDC _device_context;
    HGLRC _opengl_context;
};

} /* namespace nori */

#endif /* NORI_GRAPHICS_SURFACE_H_ */
