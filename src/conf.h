#ifndef _AUTOFOV_CONF_H_
#define _AUTOFOV_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

/* Plugin Name
 *
 * Defines the plugin name as shown in X-Plane's log
 * file and in the plugin admin
 */
#define CONF_PLUGIN_NAME "AutoFoV"

/* Plugin Signature
 *
 * Defines the plugin signature as shown in X-Plane's log
 * file and in the plugin admin. The signature can also
 * be used by other plugins to check whether AutoFoV is loaded.
 */
#define CONF_PLUGIN_SIGN "net.daemotron.autofov"

/* Plugin Description
 *
 * Defines the plugin description front matter - the description
 * shown in the plugin admin will be the front matter, enhanced
 * by the plugin's version.
 */
#define CONF_PLUGIN_DESC "Automatic Field of View"

/* Plugin Version
 *
 * Defines the plugin version. The version is not directly exposed
 * to X-Plane, but is appended to the description front matter, to
 * make the version information accessible to the end user.
 */
#define CONF_PLUGIN_VERS "2.0.dev"

/* Log verbosity
 *
 * Set this to LOG_WARN for release builds, and
 * to LOG_DEBUG for development builds
 */
#define CONF_LOG_LEVEL LOG_DEBUG

/* Default Field of View
 *
 * 75 seems to be a reasonable value - only used
 * when no value can be detected.
 */
#define CONF_FOV_DEFAULT 75.0

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_CONF_H_ */
