#include <nori/main.h>
#include <nori/application.h>
#include <nori/renderer.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/image.h>
#include <nori/texture.h>

#include <boost/make_shared.hpp>

#include <stdexcept>


class basic_drawing_app : public nori::application {
public:
    basic_drawing_app()
    {
    }

    virtual bool on_initialized() {
        _texture = boost::make_shared<nori::texture>(nori::image("assets/megaman.png"));
        return true;
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("basic drawing");
    }

    virtual void render(nori::renderer& renderer) {
        renderer.render(*_texture, nori::point_f(100, 50), nori::size_f(256, 256));
    }

private:
    nori::texture_ptr _texture;
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
