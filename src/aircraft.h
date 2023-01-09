#ifndef _AUTOFOV_AIRCRAFT_H_
#define _AUTOFOV_AIRCRAFT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void aircraft_get_fov_path(char *, size_t);
float aircraft_get_fov();
void aircraft_handle_new();

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_AIRCRAFT_H_ */
