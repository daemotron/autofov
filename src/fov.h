#ifndef _AUTOFOV_FOV_H_
#define _AUTOFOV_FOV_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FOV_DATA_REF "sim/graphics/view/field_of_view_deg"

bool fov_init(void);
void fov_destroy(void);
float fov_get(void);
bool fov_set(float);

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_FOV_H_ */
