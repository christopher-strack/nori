#ifndef NORI_APPLICATION_H_
#define NORI_APPLICATION_H_

#if defined(WIN32)
#include "nori/detail/win_application.h"
#elif defined(ANDROID)
#include "nori/detail/android_application.h"
#endif


namespace nori {

#if defined(WIN32)
typedef detail::win_application application;
#elif defined(ANDROID)
typedef detail::android_application application;
#endif

} // namespace nori

#endif /* NORI_APPLICATION_H_ */
