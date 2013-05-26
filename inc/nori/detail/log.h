#ifndef NORI_DETAIL_LOG_H_
#define NORI_DETAIL_LOG_H_

#include <stdarg.h>


namespace nori {

enum _log_priority {
    _log_info,
    _log_warning,
    _log_error
};

void _log(_log_priority priority, const char* message, va_list args);

} /* namespace nori */

#endif /* NORI_LOG_H_ */
