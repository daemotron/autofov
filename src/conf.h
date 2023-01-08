#ifndef _AUTOFOV_CONF_H_
#define _AUTOFOV_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

/* Log verbosity
 *
 * Set this to LOG_WARN for release builds, and
 * to LOG_DEBUG for development builds
 */
#define CONF_LOG_LEVEL LOG_DEBUG

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_CONF_H_ */
