#include "nori/detail/android_window.h"

#include <stdexcept>


namespace nori {
namespace detail {

android_window::android_window() {
    throw std::runtime_error("not implemented");
}

android_window::~android_window() {
    throw std::runtime_error("not implemented");
}

void android_window::set_visible(bool visible) {
    throw std::runtime_error("not implemented");
}

bool android_window::visible() const {
    throw std::runtime_error("not implemented");
}

void android_window::close() {
    throw std::runtime_error("not implemented");
}

bool android_window::closed() const {
    throw std::runtime_error("not implemented");
}

void android_window::set_size(const nori::size& size) {
    throw std::runtime_error("not implemented");
}

nori::size android_window::size() const {
    throw std::runtime_error("not implemented");
}

void android_window::set_title(const std::string& title) {
    throw std::runtime_error("not implemented");
}

std::string android_window::title() const {
    throw std::runtime_error("not implemented");
}

bool android_window::focused() const {
    throw std::runtime_error("not implemented");
}

graphics_surface_ptr android_window::graphics_surface() {
    throw std::runtime_error("not implemented");
}

void android_window::dispatch_messages() {
    throw std::runtime_error("not implemented");
}

} /* namespace detail */
} /* namespace nori */
