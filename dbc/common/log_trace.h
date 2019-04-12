#ifndef __LOG_DEBUG_TRACE_H__
#define __LOG_DEBUG_TRACE_H__

#include "sys_inc.h"
#include "version.h"


#define LOG_DEBUG_TRACE_ENABLE

#if defined(LOG_DEBUG_TRACE_ENABLE)
#define LOG_DEBUG_TRACE_DAEMON(format, args...) \
	do { \
		/*daemon_log(LOG_INFO, */printf("[%s]:%d " format, \
			__FUNCTION__, __LINE__, ## args); \
	} while (0)
#else
#define LOG_DEBUG_TRACE_DAEMON(format, args...)
#endif

#if defined(LOG_DEBUG_TRACE_ENABLE)
#define LOG_DEBUG_TRACE_PERROR(format, args...) \
	do { \
		/*daemon_log(LOG_INFO, */printf("[%s]:%d [error info(errno=%d): %s] -> " format, \
			__FUNCTION__, __LINE__, errno, strerror(errno), ## args); \
	} while (0)
#else
#define LOG_DEBUG_TRACE_PERROR(format, args...)
#endif

#define LOG_DEBUG_TRACE		LOG_DEBUG_TRACE_DAEMON
#define LOG_DEBUG_PERROR	LOG_DEBUG_TRACE_PERROR

#endif

