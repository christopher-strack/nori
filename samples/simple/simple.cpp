#include <nori/main.h>
#include <nori/application.h>


class sample_app : public nori::application {
public:
    virtual void on_window_created(nori::window& window) {
        window.set_size(nori::size(1024, 768));
        window.set_title("simple sample");
    }
};


int nori_main() {
    sample_app app;

    app.run();

    return 0;
}
