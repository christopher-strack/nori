#include "nori/detail/log.h"
#include "nori/detail/windows_fwd.h"

#include <sstream>
#include <stdio.h>
#include <stdarg.h>


namespace {

const char* priority_to_tag(nori::detail::log_priority priority);

} /* anonymous namespace */


namespace nori {
namespace detail {

void log(log_priority priority, const char* message, va_list args) {
    char buffer[1024];
    vsnprintf_s(buffer, 1024, message, args);

    std::stringstream str;
    str << priority_to_tag(priority) << " " << buffer << std::endl;

    ::OutputDebugStringA(str.str().c_str());
}

} /* namespace detail */
} /* namespace nori */


namespace {

const char* priority_to_tag(nori::detail::log_priority priority) {
    const char* tag = "";

    switch (priority) {
    case nori::detail::log_info:
        tag = "[INFO]";
        break;
    case nori::detail::log_warning:
        tag = "[WARNING]";
        break;
    case nori::detail::log_error:
        tag = "[ERROR]";
        break;
    }

    return tag;
}

} /* anonymous namespace */
