#include "nori/log.h"
#include "nori/detail/windows_fwd.h"

#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <sstream>


namespace {

const char* priority_to_tag(nori::log_priority priority);

} /* anonymous namespace */


namespace nori {

void log(log_priority priority, const char* message, ...) {
    va_list args;
    va_start(args, message);

    char buffer[1024];
    vsnprintf_s(buffer, 1024, message, args);

    va_end(args);

    std::stringstream str;
    str << priority_to_tag(priority) << " " << buffer << std::endl;

    ::OutputDebugStringA(str.str().c_str());
}

} /* namespace nori */


namespace {

const char* priority_to_tag(nori::log_priority priority) {
    const char* tag = "";

    switch (priority) {
    case nori::LOG_INFO:
        tag = "[INFO]";
        break;
    case nori::LOG_WARNING:
        tag = "[WARNING]";
        break;
    case nori::LOG_ERROR:
        tag = "[ERROR]";
        break;
    case nori::LOG_FATAL:
        tag = "[FATAL]";
        break;
    }

    return tag;
}

} /* anonymous namespace */
