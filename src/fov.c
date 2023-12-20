#include <stdbool.h>
#include <stddef.h>

#include <XPLMDataAccess.h>

#include <xppl_float.h>
#include <xppl_log.h>

#include "conf.h"
#include "fov.h"


static XPLMDataRef FoV_Ref = NULL;
static int FoV_Initialized = false;


bool
fov_init(void)
{
    FoV_Ref = XPLMFindDataRef(FOV_DATA_REF);
    if (FoV_Ref == NULL || !XPLMIsDataRefGood(FoV_Ref))
    {
        FoV_Initialized = false;
        xppl_log_error("FoV initialisation failed: could not initialize data ref %s", FOV_DATA_REF);
        return false;
    }
    FoV_Initialized = true;
    return true;
}


void
fov_destroy(void)
{
    FoV_Ref = NULL;
}


float
fov_get(void)
{
    const float result = XPLMGetDataf(FoV_Ref);
    if (xppl_float_almost_equal_f(result, 0.0))
    {
        return CONF_FOV_DEFAULT;
    }
    return result;
}


bool
fov_set(float fov)
{
    if (FoV_Initialized && XPLMCanWriteDataRef(FoV_Ref))
    {
        XPLMSetDataf(FoV_Ref, fov);
        if (xppl_float_almost_equal_f(fov, XPLMGetDataf(FoV_Ref)))
        {
            xppl_log_debug("FoV successfully set to %f", fov);
            return true;
        }
        xppl_log_error("Failed to set FoV to %f", fov);
        return false;
    }
    xppl_log_error("Cannot set FoV: module not initialized or data ref not writeable");
    return false;
}
