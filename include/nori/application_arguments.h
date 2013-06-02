#ifndef NORI_APPLICATION_ARGUMENTS_H_
#define NORI_APPLICATION_ARGUMENTS_H_


#if defined(ANDROID)

struct android_app;

namespace nori {

struct application_arguments {
    int argc;
    char** argv;
    ::android_app* android_app;
};

}

#elif defined(WIN32)

namespace nori {

struct application_arguments {
    int argc;
    char** argv;
};

}

#endif


#endif /* NORI_APPLICATION_ARGUMENTS_H_ */
