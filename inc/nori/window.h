#ifndef NORI_WINDOW_H_
#define NORI_WINDOW_H_

#include "nori/vector2.h"
#include "nori/detail/graphics_surface_fwd.h"

#include <boost/shared_ptr.hpp>
#include <string>

#if defined(WIN32)
#include "nori/detail/win_window.h"
#elif defined(ANDROID)
#include "nori/detail/null_window.h"
#endif


namespace nori {

#if defined(WIN32)
typedef detail::win_window window;
#elif defined(ANDROID)
typedef detail::null_window window;
#endif

} /* namespace nori */

#endif /* NORI_WINDOW_H_ */
