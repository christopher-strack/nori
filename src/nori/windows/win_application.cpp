#include "nori/detail/precompiled.h"
#include "nori/detail/win_application.h"
#include "nori/graphics_surface.h"
#include "nori/renderer.h"

#include <memory>


namespace nori {
namespace detail {

void win_application::run(const nori::application_arguments& arguments) {
    _window = std::make_shared<window>();
    on_window_created(*_window);
    graphics_surface_ptr surface = _window->graphics_surface();
    renderer renderer(surface);

    if (on_initialized()) {
        _window->set_visible(true);

        while (!_window->closed()) {
            _window->dispatch_messages();

            if (_window->focused()) {
                surface->clear();
                render(renderer);
                surface->swap();
            }
        }
    }
}

} // namespace detail
} // namespace nori
