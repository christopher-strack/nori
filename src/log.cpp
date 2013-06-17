#include "nori/log.h"
#include "nori/detail/log.h"

#include <string>


namespace nori {

void log_info(const char* message, ...) {
    va_list args;
    va_start(args, message);
    detail::log(detail::log_info, message, args);
    va_end(args);
}

void log_warning(const char* message, ...) {
    va_list args;
    va_start(args, message);
    detail::log(detail::log_warning, message, args);
    va_end(args);
}

void log_error(const char* message, ...) {
    va_list args;
    va_start(args, message);
    detail::log(detail::log_error, message, args);
    va_end(args);
}

} // namespace nori
