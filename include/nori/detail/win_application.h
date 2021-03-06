#ifndef NORI_WIN_APPLICATION_H_
#define NORI_WIN_APPLICATION_H_

#include "nori/window.h"
#include "nori/application_arguments.h"
#include "nori/detail/renderer_fwd.h"

#include <memory>


namespace nori {
namespace detail {

class win_application {
public:
    void run(const nori::application_arguments& arguments);

protected:
    virtual bool on_initialized() { return true; }
    virtual void on_window_created(window& window) {}

    virtual void update(float elapsed_seconds) {}
    virtual void render(renderer& renderer) {}

private:
    std::shared_ptr<nori::window> _window;
};

} // namespace detail
} // namespace nori

#endif // NORI_WIN_APPLICATION_H_
