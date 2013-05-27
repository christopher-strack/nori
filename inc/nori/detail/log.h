#ifndef NORI_DETAIL_LOG_H_
#define NORI_DETAIL_LOG_H_

#include <stdarg.h>


namespace nori {
namespace detail {

enum log_priority {
    log_info,
    log_warning,
    log_error
};

void log(log_priority priority, const char* message, va_list args);

} /* namespace detail */
} /* namespace nori */

#endif /* NORI_DETAIL_LOG_H_ */
