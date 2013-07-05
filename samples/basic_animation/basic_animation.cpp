#include <nori/main.h>
#include <nori/application.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/scene.h>
#include <nori/animation.h>
#include <nori/slicer.h>

#include <memory>
#include <stdexcept>

#include <boost/range/counting_range.hpp>


class basic_animation_app : public nori::application {
public:
    virtual bool on_initialized() {
        auto node = _scene.add_sprite(
            "assets/megaman_idle_walk.png",
            nori::grid_slicer(35, 43));
        node->set_position(nori::point(100, 500));
        node->set_size(nori::size(35 * 3, 43 * 3));
        node->set_animation(
            nori::animation(boost::counting_range(0, 7))
                .set_speed(0.2f));
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic animation");
    }

    virtual void update(float elapsed_seconds) {
        _scene.update(elapsed_seconds);
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
