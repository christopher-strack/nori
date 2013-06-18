#include "nori/detail/precompiled.h"
#include "nori/detail/android_application.h"
#include "nori/detail/android_graphics_surface.h"
#include "nori/detail/android_file.h"
#include "nori/renderer.h"

#include <android_native_app_glue.h>
#include <android/native_activity.h>
#include <android/looper.h>

#include <boost/make_shared.hpp>


namespace nori {
namespace detail {

android_application::android_application()
    : _focused(false), _android_app(0)
{
}

void android_application::run(const nori::application_arguments& arguments) {
    _android_app = arguments.android_app;

    _android_app->userData = this;
    _android_app->onAppCmd = &_on_android_command_proxy;
    _android_app->onInputEvent = &_on_android_input_proxy;

    while (_android_app->destroyRequested == 0) {
        _process_android_events(_android_app);

        if (_graphics_surface && _focused) {
            _graphics_surface->clear();
            render(*_renderer);
            _graphics_surface->swap();
        }
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

void android_application::_on_android_command(android_app* app, int32_t cmd) {
    switch (cmd) {
    case APP_CMD_INIT_WINDOW:
        _graphics_surface = boost::make_shared<android_graphics_surface>(app->window);
        _renderer = boost::make_shared<renderer>(_graphics_surface);
        if (!on_initialized()) {
            _renderer.reset();
            _graphics_surface.reset();
            ::ANativeActivity_finish(_android_app->activity);
        }
        break;
    case APP_CMD_TERM_WINDOW:
        _renderer.reset();
        _graphics_surface.reset();
        break;

    case APP_CMD_GAINED_FOCUS:
    case APP_CMD_LOST_FOCUS:
        _focused = cmd == APP_CMD_GAINED_FOCUS;
        break;
    }
}

void android_application::_on_android_input(android_app* app, AInputEvent* event) {
}


void android_application::_on_android_command_proxy(
    android_app* app,
    int32_t cmd)
{
    android_application* application = (android_application*)app->userData;
    application->_on_android_command(app, cmd);
}

int32_t android_application::_on_android_input_proxy(
    android_app* app,
    AInputEvent* event)
{
    android_application* application = (android_application*)app->userData;
    application->_on_android_input(app, event);
    return 0;
}

} // namespace detail
} // namespace nori
