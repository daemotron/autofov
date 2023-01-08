#include <stdio.h>
#include <string.h>

#include <CHeaders/XPLM/XPLMDataAccess.h>

#include "conf.h"
#include "fov.h"
#include "log.h"


float Default_FoV = CONF_FOV_DEFAULT;
int Default_FoV_Initialized = 0;


float
fov_get()
{
    return XPLMGetDataf(XPLMFindDataRef("sim/graphics/view/field_of_view_deg"));
}


void
fov_init()
{
    if(Default_FoV_Initialized == 0)
    {
        Default_FoV = fov_get();
        Default_FoV_Initialized = 1;
        char msg[200];
        memset(msg, '\0', 200);
        sprintf(msg, "Default field of view initialized as %.2f°", Default_FoV);
        log_debug(msg);
    }
}


void
fov_set(float fov)
{
    XPLMSetDataf(XPLMFindDataRef("sim/graphics/view/field_of_view_deg"), fov);
}
