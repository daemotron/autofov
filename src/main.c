#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <XPLMPlugin.h>
#include <XPLMUtilities.h>

#include <xppl.h>
#include <xppl_log.h>
#include <xppl_config.h>

#include "aircraft.h"
#include "conf.h"
#include "fov.h"


static xppl_config_ctx_t Cfg_Ctx;


PLUGIN_API int
XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strncpy(outName, CONF_PLUGIN_NAME, 255);
    strncpy(outSig, CONF_PLUGIN_SIGN, 255);
    snprintf(outDesc, 255, "%s version %s", CONF_PLUGIN_DESC, CONF_PLUGIN_VERS);

    XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

    xppl_log_init(XPLMDebugString, CONF_LOG_LEVEL_DEFAULT, "AUTOFOV");
    xppl_log_info("%s version %s", CONF_PLUGIN_NAME, CONF_PLUGIN_VERS);

    if (!fov_init())
    {
        xppl_log_error("Plugin initialisation failed, stopping %s", CONF_PLUGIN_NAME);
        return 0;
    }

    long double default_fov = (long double)fov_get();

    xppl_config_init(&Cfg_Ctx, "AutoFoV Configuration", CONF_FILE, XPLMGetDirectorySeparator(), true);
    xppl_config_register(&Cfg_Ctx, "fov_default", XPPL_CONFIG_FLOAT, &default_fov, "Default FoV to be used when no aircraft-specific FoV is defined");
    xppl_config_load(&Cfg_Ctx);

    return 1;
}


PLUGIN_API void
XPluginStop(void)
{
    xppl_config_destroy(&Cfg_Ctx);
    xppl_log_destroy();
}


PLUGIN_API void
XPluginDisable(void)
{

}


PLUGIN_API int
XPluginEnable(void)
{
    xppl_config_load(&Cfg_Ctx);
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
            aircraft_handle_new((float)xppl_config_data_get_f(&Cfg_Ctx, "fov_default"));
        }
    }
}
