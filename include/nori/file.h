#ifndef NORI_FILE_H_
#define NORI_FILE_H_


#if defined(WIN32)
#include "nori/detail/stl_file.h"
#elif defined(ANDROID)
#include "nori/detail/android_file.h"
#endif


namespace nori {

#if defined(WIN32)
typedef detail::stl_file file;
#elif defined(ANDROID)
typedef detail::android_file file;
#endif

} // namespace nori

#endif /* NORI_FILE_H_ */
