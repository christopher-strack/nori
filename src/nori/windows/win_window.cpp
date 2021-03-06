#include "nori/detail/precompiled.h"
#include "nori/detail/win_window.h"
#include "nori/detail/win_graphics_surface.h"

#include <memory>
#include <stdexcept>
#include <sstream>


namespace {

std::string _create_unique_class_name();

} // anonymous namespace


namespace nori {
namespace detail {

const nori::size win_window::default_size = nori::size(800, 600);

win_window::win_window()
    : _closed(false), _focused(false)
{
    if (!_create()) {
        throw std::runtime_error("Couldn't create window");
    }

    set_size(default_size);
}

win_window::~win_window() {
    _graphics_surface = 0;

    HINSTANCE hinstance = ::GetModuleHandle(0);
    ::DestroyWindow(_handle);
    ::UnregisterClass(_class_name.c_str(), hinstance);
}

void win_window::set_visible(bool visible) {
    if (visible) {
        ::UpdateWindow(_handle);
        ::ShowWindow(_handle, SW_SHOWNORMAL);
    }
    else {
        ::UpdateWindow(_handle);
        ::ShowWindow(_handle, SW_HIDE);
    }
}

bool win_window::visible() const {
    return ::IsWindowVisible(_handle) == TRUE;
}

void win_window::close() {
    _closed = true;
    ::DestroyWindow(_handle);
}

bool win_window::closed() const {
    return _closed;
}

void win_window::set_size(const nori::size& size) {
    RECT rect;
    ::GetWindowRect(_handle, &rect);
    rect.right = rect.left + size.x;
    rect.bottom = rect.top + size.y;
    ::AdjustWindowRect(&rect, _style, FALSE);
    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;
    ::MoveWindow(_handle, rect.left, rect.top, width, height, FALSE);
}

size win_window::size() const {
    RECT rect;
    ::GetClientRect(_handle, &rect);
    return nori::size(rect.right - rect.left, rect.bottom - rect.top);
}

void win_window::set_title(const std::string& title) {
    _title = title;
    ::SetWindowTextA(_handle, title.c_str());
}

std::string win_window::title() const {
    return _title;
}

bool win_window::focused() const {
    return visible() && _focused;
}

graphics_surface_ptr win_window::graphics_surface() {
    if (_graphics_surface == 0) {
        _graphics_surface = std::make_shared<win_graphics_surface>(*this);
    }

    return _graphics_surface;
}

HWND win_window::handle() const {
    return _handle;
}

void win_window::dispatch_messages() {
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}

bool win_window::_create() {
    _class_name = _create_unique_class_name();
    HINSTANCE hinstance = ::GetModuleHandle(0);
    WNDCLASSEX window_class;
    window_class.cbSize        = sizeof(WNDCLASSEX);
    window_class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc   = &_window_proc;
    window_class.cbClsExtra    = 0;
    window_class.cbWndExtra    = 0;
    window_class.hInstance     = hinstance;
    window_class.hIcon         = ::LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
    window_class.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
    window_class.lpszMenuName  = NULL;
    window_class.lpszClassName = _class_name.c_str();
    window_class.hIconSm       = ::LoadIcon(window_class.hInstance,
        MAKEINTRESOURCE(IDI_APPLICATION));

    if (::RegisterClassEx(&window_class)) {
        _style = WS_OVERLAPPEDWINDOW;
        _handle = ::CreateWindowEx(
            0, _class_name.c_str(), "",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            default_size.x, default_size.y,
            0, 0,
            hinstance, 0);

        ::SetWindowLong(_handle, GWL_USERDATA, reinterpret_cast<LONG>(this));
    }

    return _handle != 0;
}

void win_window::_handle_message(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch(message) {
    case WM_ACTIVATE:
        _focused = !HIWORD(wparam);
        break;
    case WM_CLOSE:
        _closed = true;
        break;
    }
}

LRESULT CALLBACK win_window::_window_proc(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    const LONG window_ptr = ::GetWindowLong(hwnd, GWL_USERDATA);
    nori::detail::win_window* window =
        reinterpret_cast<nori::detail::win_window*>(window_ptr);
    if (window) {
        window->_handle_message(hwnd, message, wparam, lparam);
    }
    return ::DefWindowProc(hwnd, message, wparam, lparam);
}

} // namespace detail
} // namespace nori


namespace {

std::string _create_unique_class_name() {
    static int window_counter = 0;
    std::stringstream stream;
    stream << "window_class_" << window_counter;
    window_counter++;

    return stream.str();
}

} // anonymous namespace
