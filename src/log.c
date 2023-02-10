#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>

#include "conf.h"
#include "core.h"
#include "log.h"


int MaxLogLevel = CONF_LOG_LEVEL_DEFAULT;
static XPLMDataRef time_ref = NULL;


void
log_msg_v(int level, const char *message, va_list args)
{
    /* don't log anything below the set log level */
    if (level < MaxLogLevel)
    {
        return;
    }

    /* retrieve data ref for time */
    if (time_ref == NULL)
    {
        time_ref = XPLMFindDataRef("sim/network/misc/network_time_sec");
    }

    /* retrieve data for the time stamp (X-Plane convention) */
    int hrs, min;
    float sec, real_time = XPLMGetDataf(time_ref);
	hrs = (int)(real_time / 3600.0f);
	min = (int)(real_time / 60.0f) - (int)(hrs * 60.0f);
	sec = real_time - (hrs * 3600.0f) - (min * 60.0f);

    /* retrieve the log level string */
    char lvl[6];
    switch (level)
    {
        case LOG_DEBUG:
            strncpy(lvl, "DEBUG", 6);
            break;
        
        case LOG_INFO:
            strncpy(lvl, " INFO", 6);
            break;
        
        case LOG_WARN:
            strncpy(lvl, " WARN", 6);
            break;
        
        case LOG_ERROR:
            strncpy(lvl, "ERROR", 6);
            break;
        
        default:
            strncpy(lvl, "INVAL", 6);
            break;
    }

    /* create the message by rolling in eventual arguments */
    char msg_buffer[LOG_BUFSIZE + 1];
    memset(msg_buffer, '\0', LOG_BUFSIZE + 1);
    vsnprintf(msg_buffer, LOG_BUFSIZE, message, args);
    
    /* prepare the log buffer and send it to log.txt */
    char log_buffer[LOG_BUFSIZE + 64];
    memset(log_buffer, '\0', LOG_BUFSIZE + 64);
	snprintf(log_buffer, LOG_BUFSIZE + 64, "%d:%02d:%06.3f [AutoFoV]: %s: %s\n", hrs, min, sec, lvl, msg_buffer);
    XPLMDebugString(log_buffer);
}


void
log_msg(int level, const char *message, ...)
{
    va_list args;
    
    va_start(args, message);
    log_msg_v(level, message, args);
    va_end(args);
}


void
log_debug(const char *message, ...)
{
    va_list args;
    
    va_start(args, message);
    log_msg_v(LOG_DEBUG, message, args);
    va_end(args);
}


void
log_info(const char *message, ...)
{
    va_list args;
    
    va_start(args, message);
    log_msg_v(LOG_INFO, message, args);
    va_end(args);
}


void
log_warn(const char *message, ...)
{
    va_list args;
    
    va_start(args, message);
    log_msg_v(LOG_WARN, message, args);
    va_end(args);
}


void
log_error(const char *message, ...)
{
    va_list args;
    
    va_start(args, message);
    log_msg_v(LOG_ERROR, message, args);
    va_end(args);
}


int
log_level_parse(const char *level)
{
    size_t len = strlen(level);

    if (strncmp(level, "debug", MIN(len, 5)) == 0)
    {
        return LOG_DEBUG;
    }
    if (strncmp(level, "info", MIN(len, 4)) == 0)
    {
        return LOG_INFO;
    }
    if ((strncmp(level, "warn", MIN(len, 4)) == 0) || (strncmp(level, "warning", MIN(len, 7)) == 0))
    {
        return LOG_WARN;
    }
    if (strncmp(level, "error", MIN(len, 5)) == 0)
    {
        return LOG_ERROR;
    }

    /* invalid log level string */
    return -1;
}


const char *
log_level_string(int level)
{
    if (level == LOG_DEBUG)
    {
        return "debug";
    }
    if (level == LOG_INFO)
    {
        return "info";
    }
    if (level == LOG_WARN)
    {
        return "warn";
    }
    if (level == LOG_ERROR)
    {
        return "error";
    }

    /* invalid log level */
    return NULL;
}


void
log_set_level(int level)
{
    MaxLogLevel = level;
}
