#ifndef NORI_ANDROID_APPLICATION_H_
#define NORI_ANDROID_APPLICATION_H_

#include "nori/window.h"
#include "nori/application_arguments.h"


struct android_app;
struct AInputEvent;


namespace nori {
namespace detail {

class android_application {
public:
    void run(const nori::application_arguments& arguments);

protected:
    virtual void on_window_created(window& window) {}

    virtual void draw() {}

private:
    void _process_android_events(android_app* app);
    void _on_android_command(int32_t cmd);
    void _on_android_input(AInputEvent* event);

    static void _on_android_command_proxy(android_app* app, int32_t cmd);
    static int32_t _on_android_input_proxy(android_app* app, AInputEvent* event);
};

} /* namespace detail */
} /* namespace nori */


#endif /* NORI_ANDROID_APPLICATION_H_ */