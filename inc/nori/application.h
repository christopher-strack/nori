#ifndef NORI_APPLICATION_H_
#define NORI_APPLICATION_H_

#include "nori/window.h"


namespace nori {

class application {
public:
    void run();

protected:
    virtual void on_window_created(window& window) {}

private:
    window _window;
};

} /* namespace nori */

#endif /* NORI_APPLICATION_H_ */
