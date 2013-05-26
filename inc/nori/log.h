#ifndef NORI_LOG_H_
#define NORI_LOG_H_

#include "nori/detail/log.h"


namespace nori {

void log(const char* message, ...);
void log_warning(const char* message, ...);
void log_error(const char* message, ...);

} /* namespace nori */

#endif /* NORI_LOG_H_ */
