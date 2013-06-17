#ifndef NORI_WIN_WINDOW_
#define NORI_WIN_WINDOW_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"
#include "nori/detail/windows_fwd.h"

#include <string>


namespace nori {
namespace detail {

class win_window {
public:
    win_window();
    ~win_window();

    void set_visible(bool visible);
    bool visible() const;

    void close();
    bool closed() const;

    void set_size(const nori::size& size);
    size size() const;

    void set_title(const std::string& title);
    std::string title() const;

    bool focused() const;

    graphics_surface_ptr graphics_surface();

    HWND handle() const;

    void dispatch_messages();


    static const nori::size default_size;

private:
    bool _create();

    void _handle_message(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

    static LRESULT CALLBACK _window_proc(
        HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

    bool _closed;
    bool _focused;
    std::string _title;
    HWND _handle;
    DWORD _style;
    std::string _class_name;

    graphics_surface_ptr _graphics_surface;
};

} // namespace detail
} // namespace nori

#endif // NORI_WIN_WINDOW_
