#include <nori/main.h>
#include <nori/application.h>


class sample_app : public nori::application {
public:

};


int nori_main() {
    sample_app app;

    app.run();

    return 0;
}
