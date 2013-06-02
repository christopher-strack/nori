#ifndef NORI_MAIN_H_
#define NORI_MAIN_H_


#include "nori/application_arguments.h"


extern int nori_main(const nori::application_arguments& arguments);


#if defined(ANDROID)

#include <android_native_app_glue.h>


void android_main(android_app* app) {
    nori::application_arguments args = { 0, 0, app };
    app_dummy(); // Make sure glue isn't stripped.
    nori_main(args);
}

#elif defined(WIN32)

int main(int argc, char** argv) {
    nori::application_arguments args = { argc, argv };
    return nori_main(args);
}

#endif


#endif /* NORI_MAIN_H_ */
