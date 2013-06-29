#include <nori/main.h>
#include <nori/application.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/scene.h>
#include <nori/sprite.h>

#include <memory>
#include <stdexcept>


class basic_animation_app : public nori::application {
public:
    virtual bool on_initialized() {
        auto megaman = nori::make_sprite(
            "assets/megaman_idle_walk.png",
            nori::size(35, 43));
        auto node = _scene.add_sprite(megaman);
        node->set_position(nori::point(100, 500));
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic animation");
    }

    virtual void render(nori::renderer& renderer) {
        _scene.render(renderer);
    }

private:
    nori::scene _scene;
};


int nori_main(const nori::application_arguments& arguments) {
    try {
        basic_animation_app app;
        app.run(arguments);
    }
    catch (const std::runtime_error& error) {
        nori::log_error(error.what());
    }

    return 0;
}
