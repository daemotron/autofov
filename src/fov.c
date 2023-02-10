#include <XPLMDataAccess.h>

#include "conf.h"
#include "fov.h"
#include "log.h"


static float Default_FoV = CONF_FOV_DEFAULT;
static XPLMDataRef FoV_Ref = NULL;
static int Default_FoV_Initialized = 0;


float
fov_get()
{
    return XPLMGetDataf(FoV_Ref);
}


void
fov_init()
{
    if (FoV_Ref == NULL)
    {
        FoV_Ref = XPLMFindDataRef("sim/graphics/view/field_of_view_deg");
    }

    if (Default_FoV_Initialized == 0)
    {
        Default_FoV = fov_get();
        Default_FoV_Initialized = 1;
        log_debug("Default field of view initialized as %.2f°", Default_FoV);
    }
}


void
fov_set(float fov)
{
    XPLMSetDataf(FoV_Ref, fov);
}


void
fov_set_default()
{
    fov_set(Default_FoV);
}
