#ifndef NORI_APPLICATION_H_
#define NORI_APPLICATION_H_

#include "nori/window.h"


namespace nori {

class application {
public:
    void run();

private:
    window _window;
};

} /* namespace nori */

#endif /* NORI_APPLICATION_H_ */
