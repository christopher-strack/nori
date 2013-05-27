#include "nori/detail/log.h"

#include <stdarg.h>
#include <stdexcept>


namespace nori {
namespace detail {

void log(log_priority priority, const char* message, va_list args) {
    throw std::runtime_error("not implemented");
}

} /* namespace detail */
} /* namespace nori */
