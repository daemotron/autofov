#include <string.h>

#include <XPLMPlugin.h>
#include <XPLMUtilities.h>
#include <xppl.h>

#include "aircraft.h"
#include "conf.h"
#include "fov.h"


PLUGIN_API int
XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strcpy(outName, CONF_PLUGIN_NAME);
    strcpy(outSig, CONF_PLUGIN_SIGN);
    strcpy(outDesc, CONF_PLUGIN_DESC);
    strcat(outDesc, " version ");
    strcat(outDesc, CONF_PLUGIN_VERS);

    XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

    xppl_init(XPLMDebugString, CONF_LOG_LEVEL_DEFAULT, "AUTOFOV");
    xppl_log_info("%s version %s", CONF_PLUGIN_NAME, CONF_PLUGIN_VERS);

    return 1;
}


PLUGIN_API void
XPluginStop(void)
{
    xppl_destroy();
}

PLUGIN_API void
XPluginDisable(void)
{

}


PLUGIN_API int
XPluginEnable(void)
{
    fov_init();
    return 1;
}


PLUGIN_API void
XPluginReceiveMessage(XPLMPluginID from, int msg, void *param)
{
    xppl_unused(from);

    if (msg == XPLM_MSG_PLANE_LOADED)
    {
        if (param == 0)
        {
            xppl_log_info("Change of primary aircraft detected");
            aircraft_handle_new();
        }
    }
    else if (msg == XPLM_MSG_WILL_WRITE_PREFS)
    {
        xppl_log_info("Restoring default FoV before X-Plane writes its preferences");
        fov_set_default();
    }
}
