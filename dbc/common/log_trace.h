#ifndef __LOG_TRACE_H__
#define __LOG_TRACE_H__

#include "sys_inc.h"

#define LOG_TRACE_ENABLE

#if defined(LOG_TRACE_ENABLE)
#define LOG_TRACE_DAEMON(format, args...) \
	do { \
		/*daemon_log(LOG_INFO, */printf("[%s][%s]:%d " format, \
			MODULE_NAME, __FUNCTION__, __LINE__, ## args); \
	} while (0)
#else
#define LOG_TRACE_DAEMON(format, args...)
#endif

#if defined(LOG_TRACE_ENABLE)
#define LOG_TRACE_PERROR(format, args...) \
	do { \
		/*daemon_log(LOG_INFO, */printf("[%s][%s]:%d [error info(errno=%d): %s] -> " format, \
			MODULE_NAME, __FUNCTION__, __LINE__, errno, strerror(errno), ## args); \
	} while (0)
#else
#define LOG_TRACE_PERROR(format, args...)
#endif

#define LOG_TRACE	LOG_TRACE_DAEMON
#define LOG_PERROR	LOG_TRACE_PERROR

#endif

