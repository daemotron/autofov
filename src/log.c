#include <stdio.h>
#include <string.h>

#include <CHeaders/XPLM/XPLMDataAccess.h>
#include <CHeaders/XPLM/XPLMUtilities.h>

#include "conf.h"
#include "core.h"
#include "log.h"


void
log_msg(int level, const char *message)
{
    /* don't log anything below the set log level */
    if (level < CONF_LOG_LEVEL)
    {
        return;
    }

    /* retrieve data for the time stamp (X-Plane convention) */
    float hrs, min, sec, real_time = XPLMGetDataf(XPLMFindDataRef("sim/network/misc/network_time_sec"));
	hrs = (int)(real_time / 3600.0f);
	min = (int)(real_time / 60.0f) - (int)(hrs * 60.0f);
	sec = real_time-(hrs * 3600.0f) - (min * 60.0f);

    /* retrieve the log level string */
    char lvl[6];
    switch (level)
    {
        case LOG_DEBUG:
            strcpy(lvl, "DEBUG");
            break;
        
        case LOG_INFO:
            strcpy(lvl, " INFO");
            break;
        
        case LOG_WARN:
            strcpy(lvl, " WARN");
            break;
        
        case LOG_ERROR:
            strcpy(lvl, "ERROR");
            break;
        
        default:
            strcpy(lvl, "INVAL");
            break;
    }
    /* make sure to not use more than the first 200 characters of the message */
    char msg[201];
    memset(msg, '\0', 201);
    memcpy(msg, message, MIN(strlen(message), 201));

    /* prepare the log buffer and send it to log.txt */
    char buffer[256];
	sprintf(buffer, "%d:%02d:%06.3f AFV: %s: %s\n", (int)hrs, (int)min, sec, lvl, msg);
    XPLMDebugString(buffer);
}


void
log_debug(const char *message)
{
    log_msg(LOG_DEBUG, message);
}


void
log_info(const char *message)
{
    log_msg(LOG_INFO, message);
}


void
log_warn(const char *message)
{
    log_msg(LOG_WARN, message);
}


void
log_error(const char *message)
{
    log_msg(LOG_ERROR, message);
}
