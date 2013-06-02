#ifndef NORI_WIN_APPLICATION_H_
#define NORI_WIN_APPLICATION_H_

#include "nori/window.h"


namespace nori {
namespace detail {

class win_application {
public:
    void run();

protected:
    virtual void on_window_created(window& window) {}

    virtual void draw() {}
};

} /* namespace detail */
} /* namespace nori */

#endif /* NORI_WIN_APPLICATION_H_ */
