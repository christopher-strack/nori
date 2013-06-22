#include <nori/main.h>
#include <nori/application.h>
#include <nori/renderer.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/image.h>
#include <nori/texture_atlas.h>
#include <nori/rectangle.h>

#include <memory>
#include <stdexcept>


class basic_drawing_app : public nori::application {
public:
    virtual bool on_initialized() {
        _texture = std::make_shared<nori::texture_atlas>();
        _texture->add(nori::image("assets/megaman.png"), _coords);
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic drawing");
    }

    virtual void render(nori::renderer& renderer) {
        renderer.render(
            *_texture, _coords,
            nori::point_f(100, 50), nori::size_f(256, 256));
    }

private:
    nori::rectangle_f _coords;
    nori::texture_atlas_ptr _texture;
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
