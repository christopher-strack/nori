#include "nori/detail/android_application.h"

#include <android_native_app_glue.h>
#include <android/native_activity.h>
#include <android/looper.h>


namespace nori {
namespace detail {

void android_application::run(const nori::application_arguments& arguments) {
    arguments->userData = this;
    arguments->onAppCmd = &_on_android_command_proxy;
    arguments->onInputEvent = &_on_android_input_proxy;

    while (arguments->destroyRequested == 0) {
        _process_android_events(arguments);
    }
}

void android_application::_process_android_events(android_app* app) {
    int ident;
    int events;
    android_poll_source* source;

    while ((ident = ALooper_pollAll(0, 0, &events, (void**)&source)) >= 0) {
        if (source != 0) {
            source->process(app, source);
        }
    }
}

void android_application::_on_android_command(int32_t cmd) {
}

void android_application::_on_android_input(AInputEvent* event) {
}


void android_application::_on_android_command_proxy(
    android_app* app,
    int32_t cmd)
{
    android_application* application = (android_application*)app->userData;
    application->_on_android_command(cmd);
}

int32_t android_application::_on_android_input_proxy(
    android_app* app,
    AInputEvent* event)
{
    android_application* application = (android_application*)app->userData;
    application->_on_android_input(event);
    return 0;
}

} /* namespace detail */
} /* namespace nori */
