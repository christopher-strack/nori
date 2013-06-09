#include "nori/detail/win_application.h"
#include "nori/graphics_surface.h"
#include "nori/graphics.h"

#include <boost/make_shared.hpp>


namespace nori {
namespace detail {

void win_application::run(const nori::application_arguments& arguments) {
    _window = boost::make_shared<window>();
    on_window_created(*_window);
    graphics_surface_ptr surface = _window->graphics_surface();
    on_initialized();
    _window->set_visible(true);

    graphics graphics;

    while (!_window->closed()) {
        _window->dispatch_messages();

        if (_window->focused()) {
            surface->clear();
            draw(graphics);
            surface->swap();
        }
    }
}

void win_application::shutdown() {
    if (_window) {
        _window->close();
    }
}

} /* namespace detail */
} /* namespace nori */
