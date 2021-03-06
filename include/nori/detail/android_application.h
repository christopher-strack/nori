#ifndef NORI_ANDROID_APPLICATION_H_
#define NORI_ANDROID_APPLICATION_H_

#include "nori/window.h"
#include "nori/application_arguments.h"
#include "nori/detail/graphics_surface_fwd.h"
#include "nori/detail/renderer_fwd.h"


struct android_app;
struct AInputEvent;


namespace nori {
namespace detail {

class android_application {
public:
    android_application();

    void run(const nori::application_arguments& arguments);

protected:
    virtual bool on_initialized() { return true; }
    virtual void on_window_created(window& window) {}

    virtual void update(float elapsed_seconds) {}
    virtual void render(renderer& renderer) {}

private:
    void _process_android_events(android_app* app);
    void _on_android_command(android_app* app, int32_t cmd);
    void _on_android_input(android_app* app, AInputEvent* event);

    static void _on_android_command_proxy(android_app* app, int32_t cmd);
    static int32_t _on_android_input_proxy(android_app* app, AInputEvent* event);

    bool _focused;
    graphics_surface_ptr _graphics_surface;
    renderer_ptr _renderer;
    android_app* _android_app;
};

} // namespace detail
} // namespace nori


#endif // NORI_ANDROID_APPLICATION_H_
