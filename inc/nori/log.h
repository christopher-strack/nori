#ifndef NORI_LOG_H_
#define NORI_LOG_H_

namespace nori {

void log_info(const char* message, ...);
void log_warning(const char* message, ...);
void log_error(const char* message, ...);

} /* namespace nori */

#endif /* NORI_LOG_H_ */
