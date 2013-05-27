#ifndef NORI_WINDOW_H_
#define NORI_WINDOW_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"

#include <boost/shared_ptr.hpp>
#include <string>


namespace nori {

namespace detail {

#if defined(WIN32)
class win_window;
typedef win_window window_impl;
#endif

} /* namespace detail */


class window {
public:
    window();

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

private:
    boost::shared_ptr<detail::window_impl> _impl;
};

} /* namespace nori */

#endif /* NORI_WINDOW_H_ */
