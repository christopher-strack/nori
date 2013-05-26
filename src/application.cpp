#include "nori/application.h"


namespace nori {

void application::run() {
    on_window_created(_window);

    _window.set_visible(true);

    while (!_window.closed()) {
        _window.dispatch_messages();
    }
}

} /* namespace nori */
