#include "nori/detail/null_window.h"

#include <stdexcept>


namespace nori {
namespace detail {

null_window::null_window() {
}

void null_window::set_visible(bool visible) {
}

bool null_window::visible() const {
    return false;
}

void null_window::close() {
}

bool null_window::closed() const {
    return false;
}

void null_window::set_size(const nori::size& size) {
}

nori::size null_window::size() const {
    return nori::size();
}

void null_window::set_title(const std::string& title) {
}

std::string null_window::title() const {
    return "";
}

bool null_window::focused() const {
    return false;
}

graphics_surface_ptr null_window::graphics_surface() {
    return graphics_surface_ptr();
}

void null_window::dispatch_messages() {
}

} // namespace detail
} // namespace nori
