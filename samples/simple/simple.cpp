#include <nori/main.h>
#include <nori/application.h>
#include <nori/log.h>

#include <stdexcept>


class sample_app : public nori::application {
public:
    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("simple sample");
    }
};


int nori_main() {
    try {
        sample_app app;
        app.run();
    }
    catch (const std::runtime_error& error) {
        nori::log_error(error.what());
    }

    return 0;
}
