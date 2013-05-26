#include "nori/log.h"
#include "nori/detail/windows_fwd.h"

#include <stdio.h>
#include <string>
#include <sstream>


namespace {

const char* priority_to_tag(nori::_log_priority priority);

} /* anonymous namespace */


namespace nori {

void _log(_log_priority priority, const char* message, va_list args) {
    char buffer[1024];
    vsnprintf_s(buffer, 1024, message, args);

    std::stringstream str;
    str << priority_to_tag(priority) << " " << buffer << std::endl;

    ::OutputDebugStringA(str.str().c_str());
}

void log(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _log(_log_info, message, args);
    va_end(args);
}

void log_warning(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _log(_log_warning, message, args);
    va_end(args);
}

void log_error(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _log(_log_error, message, args);
    va_end(args);
}

} /* namespace nori */


namespace {

const char* priority_to_tag(nori::_log_priority priority) {
    const char* tag = "";

    switch (priority) {
    case nori::_log_info:
        tag = "[INFO]";
        break;
    case nori::_log_warning:
        tag = "[WARNING]";
        break;
    case nori::_log_error:
        tag = "[ERROR]";
        break;
    }

    return tag;
}

} /* anonymous namespace */
