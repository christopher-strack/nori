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

        float elapsed_time = 0.0f;
        while (!_window->closed()) {
            int start_time = GetTickCount();
            _window->dispatch_messages();
            update(elapsed_time);

            if (_window->focused()) {
                surface->clear();
                render(renderer);
                surface->swap();
            }

            elapsed_time = float(GetTickCount() - start_time) / 1000.0f;
        }
    }
}

} // namespace detail
} // namespace nori
