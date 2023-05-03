#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <XPLMPlanes.h>

#include "aircraft.h"
#include "core.h"
#include "fov.h"
#include "log.h"


void
aircraft_get_fov_path(char *buffer, size_t buflen)
{
    char file_name[2048];
    char path_name[2048];
    memset(file_name, '\0', 2048);
    memset(path_name, '\0', 2048);
    
    XPLMGetNthAircraftModel(0, file_name, path_name);

    memset(buffer, '\0', buflen);
    if (buflen >= (strlen(path_name) + 1))
    {
        strcpy(buffer, path_name);
        buffer[strlen(path_name)-3] = 'f';
        buffer[strlen(path_name)-2] = 'o';
        buffer[strlen(path_name)-1] = 'v';
    }
    
    /* this block is for debug logging only */
    char message[3072];
    memset(message, '\0', 3072);
    sprintf(message, "Aircraft file detected: %s", file_name);
    log_debug(message);
    memset(message, '\0', 3072);
    sprintf(message, "Aircraft path detected: %s", path_name);
    log_debug(message);
    memset(message, '\0', 3072);
    sprintf(message, "Aircraft fov file path: %s", buffer);
    log_debug(message);
}


float
aircraft_get_fov()
{
    char fov_path[2048];
    char buffer[16];
    int i = 0;
    char c = '\0';
    FILE *fov_file;
    memset(fov_path, '\0', 2048);
    memset(buffer, '\0', 16);

    aircraft_get_fov_path(fov_path, 2048);

    /* minimum path: 'x.fov' => 5 characters */
    if (strlen(fov_path) < 5)
    {
        return -1.0;
    }

    /* if the file can't be opened for whatever reason, return -1 */
    fov_file = fopen(fov_path, "r");
    if (fov_file == NULL)
    {
        return -1.0;
    }

    /* read file byte by byte as long as only figures or a decimal point are read, to a maximum of 15 characters */
    while ((c = fgetc(fov_file))!=EOF)
    {
        if ((i < 15) && (((c >= 46) && (c <= 57)) || (c == 46)))
        {
            buffer[i] = c;
            i++;
        }
        else
        {
            break;
        }
    }
    fclose(fov_file);
    return strtof(buffer, NULL);
}


void
aircraft_handle_new()
{
    float custom_fov = aircraft_get_fov();

    if ((int)roundf(custom_fov) < 0)
    {
        fov_set_default();
        log_info("No custom FoV setting found for this aircraft, setting default...");
    }
    else if ((int)roundf(custom_fov) == 0)
    {
        fov_set_default();
        log_warn("Invalid custom FoV setting found for this aircraft, setting default...");
    }
    else
    {
        char msg[200];
        memset(msg, '\0', 200);

        fov_set(custom_fov);
        sprintf(msg, "Custom FoV setting found for this aircraft, setting FoV to %.2f°", custom_fov);
        log_info(msg);
    }
}
