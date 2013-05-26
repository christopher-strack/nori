#include "nori/application.h"
#include "nori/graphics_surface.h"
#include "nori/window.h"


namespace nori {

void application::run() {
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

} /* namespace nori */
