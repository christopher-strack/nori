#include "nori/detail/log.h"

#include <android/log.h>

#include <stdarg.h>
#include <stdio.h>

namespace {

android_LogPriority convert_to_android_priority(nori::detail::log_priority priority);

} /* anonymous namespace */


namespace nori {
namespace detail {

void log_raw(const char* message, ...) {
    va_list args;
    va_start(args, message);

    __android_log_vprint(ANDROID_LOG_INFO, "nori", message, args);

    va_end(args);
}

void log(log_priority priority, const char* message, va_list args) {
    __android_log_vprint(convert_to_android_priority(priority), "nori", message, args);
}

} /* namespace detail */
} /* namespace nori */


namespace {

android_LogPriority convert_to_android_priority(nori::detail::log_priority priority) {
    android_LogPriority android_priority = ANDROID_LOG_UNKNOWN;

    switch(priority) {
    case nori::detail::log_info:
        android_priority = ANDROID_LOG_INFO;
        break;
    case nori::detail::log_warning:
        android_priority = ANDROID_LOG_WARN;
        break;
    case nori::detail::log_error:
        android_priority = ANDROID_LOG_ERROR;
        break;
    }

    return android_priority;
}

} /* anonymous namespace */
