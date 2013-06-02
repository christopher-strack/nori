#include "nori/detail/android_graphics_surface.h"

#include <android/native_window.h>
#include <stdexcept>


namespace nori {
namespace detail {

android_graphics_surface::android_graphics_surface(ANativeWindow* window) {
    const EGLint attributes[] = {
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };

    const EGLint attrib_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };

    EGLint width, height, format;
    EGLint num_configs;
    EGLConfig config;

    _display = ::eglGetDisplay(EGL_DEFAULT_DISPLAY);

    ::eglInitialize(_display, 0, 0);
    ::eglChooseConfig(_display, attributes, &config, 1, &num_configs);
    ::eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);
    ::ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    _surface = ::eglCreateWindowSurface(_display, config, window, 0);
    _context = ::eglCreateContext(_display, config, 0, attrib_list);

    if (::eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE) {
        throw std::runtime_error("eglMakeCurrent failed");
    }

    ::eglQuerySurface(_display, _surface, EGL_WIDTH, &width);
    ::eglQuerySurface(_display, _surface, EGL_HEIGHT, &height);

    _size = nori::size(width, height);
    ::glViewport(0, 0, width, height);
}

android_graphics_surface::~android_graphics_surface() {
    if (_display != EGL_NO_DISPLAY) {
        ::eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (_context != EGL_NO_CONTEXT) {
            ::eglDestroyContext(_display, _context);
        }

        if (_surface != EGL_NO_SURFACE) {
            eglDestroySurface(_display, _surface);
        }

        eglTerminate(_display);
    }

    _display = EGL_NO_DISPLAY;
    _context = EGL_NO_CONTEXT;
    _surface = EGL_NO_SURFACE;
}

const nori::size& android_graphics_surface::size() const {
    return _size;
}

void android_graphics_surface::clear() {
    ::glClearColor(0, 0, 0, 1);
    ::glClear(GL_COLOR_BUFFER_BIT);
}

void android_graphics_surface::swap() {
    ::eglSwapBuffers(_display, _surface);
}

} /* namespace detail */
} /* namespace nori */
