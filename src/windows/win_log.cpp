#include "nori/detail/log.h"
#include "nori/detail/windows_fwd.h"

#include <sstream>
#include <stdio.h>
#include <stdarg.h>


namespace nori {
namespace detail {

void log_raw(const char* message, ...) {
    va_list args;
    va_start(args, message);

    char buffer[1024];
    vsnprintf_s(buffer, 1024, message, args);
    ::OutputDebugStringA(buffer);

    va_end(args);
}

void log(log_priority priority, const char* message, va_list args) {
    char buffer[1024];
    vsnprintf_s(buffer, 1024, message, args);

    std::stringstream str;
    str << log_priority_to_tag(priority) << " " << buffer << std::endl;

    ::OutputDebugStringA(str.str().c_str());
}

} /* namespace detail */
} /* namespace nori */
