#include "nori/window.h"

#include <boost/make_shared.hpp>

#if defined(WIN32)
#include "nori/detail/win_window.h"
#elif defined(ANDROID)
#include "nori/detail/android_window.h"
#endif


namespace nori {

window::window() {
    _impl = boost::make_shared<detail::window_impl>();
}

void window::set_visible(bool visible) {
    _impl->set_visible(visible);
}

bool window::visible() const {
    return _impl->visible();
}

void window::close() {
    _impl->close();
}

bool window::closed() const {
    return _impl->closed();
}

void window::set_size(const nori::size& size) {
    _impl->set_size(size);
}

nori::size window::size() const {
    return _impl->size();
}

void window::set_title(const std::string& title) {
    _impl->set_title(title);
}

std::string window::title() const {
    return _impl->title();
}

bool window::focused() const {
    return _impl->focused();
}

nori::graphics_surface_ptr window::graphics_surface() {
    return _impl->graphics_surface();
}

void window::dispatch_messages() {
    _impl->dispatch_messages();
}

} /* namespace nori */
