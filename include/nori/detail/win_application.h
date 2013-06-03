#ifndef NORI_WIN_APPLICATION_H_
#define NORI_WIN_APPLICATION_H_

#include "nori/window.h"
#include "nori/application_arguments.h"

#include <boost/shared_ptr.hpp>


namespace nori {
namespace detail {

class win_application {
public:
    void run(const nori::application_arguments& arguments);
    void shutdown();

protected:
    virtual void on_initialized() {}
    virtual void on_window_created(window& window) {}

    virtual void draw() {}

private:
    boost::shared_ptr<nori::window> _window;
};

} /* namespace detail */
} /* namespace nori */

#endif /* NORI_WIN_APPLICATION_H_ */
