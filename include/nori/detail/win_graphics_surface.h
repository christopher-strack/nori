#ifndef NORI_WIN_GRAPHICS_SURFACE_H_
#define NORI_WIN_GRAPHICS_SURFACE_H_

#include "nori/vector2.h"
#include "nori/graphics_surface.h"
#include "nori/detail/windows_fwd.h"


namespace nori {
namespace detail {

class win_window;

class win_graphics_surface : public graphics_surface {
public:
    win_graphics_surface(const win_window& window);
    ~win_graphics_surface();

    virtual const nori::size& size() const;

    virtual void clear();
    virtual void swap();

private:
    void _initialize(const win_window& window);
    void _release();
    void _set_pixel_format(int bits);

    HWND _window_handle;
    HDC _device_context;
    HGLRC _opengl_context;
    nori::size _size;
};

} // namespace detail
} // namespace nori

#endif // NORI_WIN_GRAPHICS_SURFACE_H_
