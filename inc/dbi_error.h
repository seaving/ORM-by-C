#ifndef __DBI_ERROR_H__
#define __DBI_ERROR_H__

#include "log_trace.h"
#include "dbi_object.h"

/*
* 函数: dbi_error_debug
* 功能: 打印当前出错信息
* 参数: obj		对象实例
* 返回: 无
* 说明: 
*/
#define dbi_error_debug(obj) \
	do { \
		int dbi_errno = 0; \
		const char *errmsg; \
		dbi_instance_t *instance = (dbi_instance_t *) obj; \
		if (instance && instance->conn) \
		{ \
			dbi_errno = dbi_conn_error(instance->conn, &errmsg); \
			LOG_TRACE("dbi_errno: [ %d ], errmsg: [ %s ]\n", dbi_errno, errmsg); \
		} \
	} while (0);

/*
* 函数: dbi_error_debug
* 功能: 打印当前出错信息
* 参数: obj		对象实例
* 返回: 无
* 说明: 捕获到的信息是当前操作产生的错误信息，类似于errno
*/
//void dbi_error_debug(dbi_object_t obj);

/*
* 函数: dbi_get_errno
* 功能: 获取当前错误代码
* 参数: obj		对象实例
* 返回: int		错误码
*		- 0		表示未发现错误
* 说明: 捕获到的信息是当前操作产生的错误信息，类似于errno
*/
const int dbi_get_errno(dbi_object_t obj);

/*
* 函数: dbi_get_errmsg
* 功能: 获取当前错误信息
* 参数: obj		对象实例
* 返回: 错误信息指针
*		- NULL	无错误信息
* 说明: 捕获到的信息是当前操作产生的错误信息，类似于errno
*/
const char *dbi_get_errmsg(dbi_object_t obj);


#endif


