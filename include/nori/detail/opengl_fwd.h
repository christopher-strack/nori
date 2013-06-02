#if defined(ANDROID)
    #include <EGL/egl.h>
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#elif defined(WIN32)
    #include <gl/glew.h>
#endif
