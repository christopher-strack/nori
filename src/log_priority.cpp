#include "nori/detail/log_priority.h"


namespace nori {
namespace detail {

const char* log_priority_to_tag(nori::detail::log_priority priority) {
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
    default:
        tag = "";
        break;
    }

    return tag;
}

} /* namespace detail */
} /* namespace nori */
