#ifndef NORI_LOG_H_
#define NORI_LOG_H_

namespace nori {

enum log_priority {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
};

void log(log_priority priority, const char* message, ...);

} /* namespace nori */

#endif /* NORI_LOG_H_ */
