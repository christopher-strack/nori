#include "nori/graphics_surface.h"
#include "nori/window.h"
#include "nori/detail/opengl_fwd.h"

#include <stdexcept>


namespace nori {

graphics_surface::graphics_surface(const window& window)
    : _window_handle(window.handle()), _device_context(0), _opengl_context(0)
{
    _initialize(window);
}

graphics_surface::~graphics_surface() {
    _release();
}

const size& graphics_surface::size() const {
    return _size;
}

void graphics_surface::clear() {
    ::glClearColor(0, 0, 0, 0);
    ::glClear(GL_COLOR_BUFFER_BIT);
}

void graphics_surface::swap() {
    ::SwapBuffers(_device_context);
}

void graphics_surface::_initialize(const window& window) {
    _device_context = ::GetDC(_window_handle);

    if (_device_context == 0) {
        throw std::runtime_error("Couldn't create device context");
    }

    _set_pixel_format(16);
    _opengl_context = ::wglCreateContext(_device_context);

    if (!::wglMakeCurrent(_device_context, _opengl_context)) {
        _release();
        throw std::runtime_error("Couldn't initialize graphics surface");
    }

    if (::glewInit() != GLEW_OK) {
        _release();
        throw std::runtime_error("Couldn't initialize glew");
    }

    _size = window.size();
    ::glViewport(0, 0, _size.x, _size.y);
}

void graphics_surface::_release()
{
    if (_opengl_context) {
        ::wglMakeCurrent(0, 0);
        ::wglDeleteContext(_opengl_context);
        _opengl_context = 0;
    }

    ::ReleaseDC(_window_handle, _device_context);
}

void graphics_surface::_set_pixel_format(int bits) {
    PIXELFORMATDESCRIPTOR pixel_format_desc;
    pixel_format_desc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixel_format_desc.nVersion = 1;
    pixel_format_desc.dwFlags =
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixel_format_desc.iPixelType = PFD_TYPE_RGBA;
    pixel_format_desc.cColorBits = bits;
    pixel_format_desc.cRedBits =
        pixel_format_desc.cRedShift =
        pixel_format_desc.cGreenBits =
        pixel_format_desc.cGreenShift =
        pixel_format_desc.cBlueBits =
        pixel_format_desc.cBlueShift = 0;
    pixel_format_desc.cAlphaBits = pixel_format_desc.cAlphaShift = 0;
    pixel_format_desc.cAccumBits =
        pixel_format_desc.cAccumRedBits =
        pixel_format_desc.cAccumGreenBits =
        pixel_format_desc.cAccumBlueBits =
        pixel_format_desc.cAccumAlphaBits = 0;
    pixel_format_desc.cDepthBits = bits;
    pixel_format_desc.cStencilBits = 0;
    pixel_format_desc.cAuxBuffers = 0;
    pixel_format_desc.iLayerType = PFD_MAIN_PLANE;
    pixel_format_desc.bReserved = 0;
    pixel_format_desc.dwLayerMask =
        pixel_format_desc.dwVisibleMask =
        pixel_format_desc.dwDamageMask = 0;

    int pixel_format = ::ChoosePixelFormat(_device_context, &pixel_format_desc);
    if (pixel_format != 0) {
        ::SetPixelFormat(_device_context, pixel_format, &pixel_format_desc);
    }
}

} /* namespace nori */
