#ifndef NORI_WINDOW_H_
#define NORI_WINDOW_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"
#include "nori/detail/windows_fwd.h"

#include <string>


namespace nori {

class window {
public:
    window();
    ~window();

    void set_visible(bool visible);
    bool visible() const;

    void close();
    bool closed() const;

    void set_size(const nori::size& size);
    size size() const;

    void set_title(const std::string& title);
    std::string title() const;

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
    HWND _handle;
    DWORD _style;
    std::string _class_name;
    std::string _title;

    graphics_surface_ptr _graphics_surface;
};

} /* namespace nori */

#endif /* NORI_WINDOW_H_ */
