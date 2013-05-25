#include "nori/window.h"
#include <stdexcept>
#include <sstream>


namespace {

std::string _create_unique_class_name() {
    static int window_counter = 0;
    std::stringstream stream;
    stream << "window_class_" << window_counter;
    window_counter++;

    return stream.str();
}

} /* anonymous namespace */


namespace nori {

window::window()
    : _closed(false)
{
    if (!_create()) {
        throw std::runtime_error("Couldn't create window");
    }
}

window::~window() {
    HINSTANCE hinstance = ::GetModuleHandle(0);
    ::DestroyWindow(_handle);
    ::UnregisterClass(_class_name.c_str(), hinstance);
}

void window::set_visible(bool visible) {
    if (visible) {
        ::UpdateWindow(_handle);
        ::ShowWindow(_handle, SW_SHOWNORMAL);
    }
    else {
        ::UpdateWindow(_handle);
        ::ShowWindow(_handle, SW_HIDE);
    }
}

bool window::visible() const {
    return ::IsWindowVisible(_handle) == TRUE;
}

void window::close() {
    _closed = true;
    ::DestroyWindow(_handle);
}

bool window::closed() const {
    return _closed;
}

bool window::_create() {
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
            DEFAULT_WIDTH, DEFAULT_HEIGHT,
            0, 0,
            hinstance, 0);

        ::SetWindowLong(_handle, GWL_USERDATA, reinterpret_cast<LONG>(this));
    }

    return _handle != 0;
}

void window::_handle_message(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch(message) {
    case WM_CLOSE:
        _closed = true;
        break;
    }
}

LRESULT CALLBACK window::_window_proc(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    const LONG window_ptr = ::GetWindowLong(hwnd, GWL_USERDATA);
    nori::window* window = reinterpret_cast<nori::window*>(window_ptr);
    if (window) {
        window->_handle_message(hwnd, message, wparam, lparam);
    }
    return ::DefWindowProc(hwnd, message, wparam, lparam);
}

} /* namespace nori */
