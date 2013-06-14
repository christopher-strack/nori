#include <nori/main.h>
#include <nori/application.h>
#include <nori/renderer.h>
#include <nori/window.h>
#include <nori/log.h>
#include <nori/image.h>

#include <boost/make_shared.hpp>

#include <stdexcept>


class basic_drawing_app : public nori::application {
public:
    virtual void on_initialized() {
        _image = boost::make_shared<nori::image>("assets/image.png");
    }

    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("simple sample");
    }

    virtual void render(nori::renderer& renderer) {
    }

private:
    nori::image_ptr _image;
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
