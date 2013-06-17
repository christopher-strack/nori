#ifndef NORI_LOG_PRIORITY_H_
#define NORI_LOG_PRIORITY_H_


namespace nori {
namespace detail {

enum log_priority {
    log_info,
    log_warning,
    log_error
};

const char* log_priority_to_tag(nori::detail::log_priority priority);

} // namespace detail
} // namespace nori

#endif // NORI_LOG_PRIORITY_H_
