#ifndef NORI_WINDOW_H_
#define NORI_WINDOW_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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


    static const unsigned int DEFAULT_WIDTH = 800;
    static const unsigned int DEFAULT_HEIGHT = 600;

private:
    bool _create();

    void _handle_message(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
    
    static LRESULT CALLBACK _window_proc(
        HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

    bool _closed;
    HWND _handle;
    DWORD _style;
    std::string _class_name;
};

} /* namespace nori */

#endif /* NORI_WINDOW_H_ */
