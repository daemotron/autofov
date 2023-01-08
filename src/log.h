#ifndef _AUTOFOV_LOG_H_
#define _AUTOFOV_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 4

void log_msg(int, const char *);
void log_debug(const char *);
void log_info(const char *);
void log_warn(const char *);
void log_error(const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_LOG_H_ */
