#include "nori/detail/win_application.h"
#include "nori/graphics_surface.h"


namespace nori {
namespace detail {

void win_application::run(const nori::application_arguments& arguments) {
    nori::window window;
    on_window_created(window);
    window.set_visible(true);

    graphics_surface_ptr surface = window.graphics_surface();

    while (!window.closed()) {
        window.dispatch_messages();

        if (window.focused()) {
            surface->clear();
            draw();
            surface->swap();
        }
    }
}

} /* namespace detail */
} /* namespace nori */
