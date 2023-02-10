#ifndef _AUTOFOV_LOG_H_
#define _AUTOFOV_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 4

#define LOG_BUFSIZE 200

void log_msg(int, const char *, ...);
void log_msg_v(int, const char *, va_list);
void log_debug(const char *, ...);
void log_info(const char *, ...);
void log_warn(const char *, ...);
void log_error(const char *, ...);
int log_level_parse(const char *);
const char *log_level_string(int);
void log_set_level(int);

#ifdef	__cplusplus
}
#endif

#endif /* _AUTOFOV_LOG_H_ */
