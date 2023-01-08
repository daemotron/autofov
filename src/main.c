#include <CHeaders/XPLM/XPLMPlugin.h>

#include "core.h"
#include "log.h"


PLUGIN_API int
XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strcpy(outName, "AutoFoV");
    strcpy(outSig, "net.daemotron.autofov");
    strcpy(outDesc, "Automatically set the field of view based on the aircraft loaded.");
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
    return 1;
}


PLUGIN_API void
XPluginReceiveMessage(XPLMPluginID from, int msg, void *param)
{
    UNUSED(from);

    if (msg == XPLM_MSG_PLANE_LOADED)
    {
        /*int idx = *(int*)param;*/
        if (param == 0)
        {
            log_debug("Change of primary aircraft detected");
        }
        else
        {
            log_debug("Change of secondary aircraft detected");
        }
    }
}
