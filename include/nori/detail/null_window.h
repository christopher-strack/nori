#ifndef NORI_NULL_WINDOW_H_
#define NORI_NULL_WINDOW_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"

#include <string>


namespace nori {
namespace detail {

class null_window {
public:
    null_window();

    void set_visible(bool visible);
    bool visible() const;

    void close();
    bool closed() const;

    void set_size(const nori::size& size);
    nori::size size() const;

    void set_title(const std::string& title);
    std::string title() const;

    bool focused() const;

    graphics_surface_ptr graphics_surface();

    void dispatch_messages();
};

} // namespace detail
} // namespace nori

#endif // NORI_NULL_WINDOW_H_
