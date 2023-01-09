#ifndef _AUTOFOV_FOV_H_
#define _AUTOFOV_FOV_H_

#ifdef __cplusplus
extern "C" {
#endif

float fov_get();
void fov_init();
void fov_set(float);
void fov_set_default();

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_FOV_H_ */
