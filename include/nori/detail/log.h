#ifndef NORI_DETAIL_LOG_H_
#define NORI_DETAIL_LOG_H_

#include "nori/detail/log_priority.h"

#include <stdarg.h>


namespace nori {
namespace detail {

void log_raw(const char* message, ...);
void log(log_priority priority, const char* message, va_list args);

} // namespace detail
} // namespace nori

#endif // NORI_DETAIL_LOG_H_
