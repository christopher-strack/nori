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
        _sprite = _scene.add_sprite(
            "assets/megaman_idle_walk.png",
            nori::custom_slicer()
                .add_slices(nori::grid_slicer(35, 43).slice(nori::size(250, 43)))

                .add_slice(nori::rectangle(0,   43,  35, 86))
                .add_slice(nori::rectangle(35,  43,  70, 86))
                .add_slice(nori::rectangle(70,  43, 105, 86))
                .add_slice(nori::rectangle(105, 43, 140, 86))
                .add_slice(nori::rectangle(140, 43, 184, 86))
                .add_slice(nori::rectangle(184, 43, 228, 86))
                .add_slice(nori::rectangle(228, 43, 263, 86))
                .add_slice(nori::rectangle(263, 43, 298, 86))
                .add_slice(nori::rectangle(298, 43, 333, 86))
                .add_slice(nori::rectangle(333, 43, 377, 86))
                .add_slice(nori::rectangle(377, 43, 412, 86))
            );

        _idle_animation
            .set_sequence(boost::counting_range(0, 7))
            .set_speed(0.20f);
        _running_animation
            .set_sequence(boost::counting_range(10, 16))
            .set_speed(0.1f);

        _sprite->set_position(nori::point(100, 500));
        _sprite->set_scale(3.0f);
        _sprite->set_animation(_running_animation);
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic animation");
    }

    virtual void update(float elapsed_seconds) {
        static float x = -20.0f;
        if (x < 500) {
            _sprite->set_position(nori::point_f(x, 500));
            x += 220 * elapsed_seconds;
        }
        else
        {
            static bool idling = false;
            if (!idling) {
                _sprite->set_animation(_idle_animation);
                idling = true;
            }
        }

        _scene.update(elapsed_seconds);
    }

    virtual void render(nori::renderer& renderer) {
        _scene.render(renderer);
    }

private:
    nori::sprite_ptr _sprite;
    nori::animation _idle_animation;
    nori::animation _running_animation;
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
