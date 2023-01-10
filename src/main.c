#include <string.h>

#include <CHeaders/XPLM/XPLMPlugin.h>

#include "aircraft.h"
#include "conf.h"
#include "core.h"
#include "fov.h"
#include "log.h"


PLUGIN_API int
XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strcpy(outName, CONF_PLUGIN_NAME);
    strcpy(outSig, CONF_PLUGIN_SIGN);
    strcpy(outDesc, CONF_PLUGIN_DESC);
    strcat(outDesc, " version ");
    strcat(outDesc, CONF_PLUGIN_VERS);
    return 1;
}


PLUGIN_API void
XPluginStop(void)
{

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
    UNUSED(from);

    if (msg == XPLM_MSG_PLANE_LOADED)
    {
        if (param == 0)
        {
            log_info("Change of primary aircraft detected");
            aircraft_handle_new();
        }
    }
    else if (msg == XPLM_MSG_WILL_WRITE_PREFS)
    {
        log_info("Restoring default FoV before X-Plane writes its preferences");
        fov_set_default();
    }
}
