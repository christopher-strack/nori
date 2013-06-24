#include <nori/main.h>
#include <nori/application.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/scene.h>
#include <nori/sprite.h>

#include <memory>
#include <stdexcept>


class basic_drawing_app : public nori::application {
public:
    virtual bool on_initialized() {
        _scene.add_sprite(nori::make_sprite("assets/megaman.png"));
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic drawing");
    }

    virtual void render(nori::renderer& renderer) {
        _scene.render(renderer);
    }

private:
    nori::scene _scene;
};


int nori_main(const nori::application_arguments& arguments) {
    try {
        basic_drawing_app app;
        app.run(arguments);
    }
    catch (const std::runtime_error& error) {
        nori::log_error(error.what());
    }

    return 0;
}
