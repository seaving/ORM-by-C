#include "sys_inc.h"
#include "log_trace.h"
#include "asprintf.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* 函数: dbi_error_debug
* 功能: 打印当前出错信息
* 参数: obj		对象实例
* 返回: 无
* 说明: 
*/
/*void dbi_error_debug(dbi_object_t obj)
{
	int dbi_errno = 0;
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		dbi_errno = dbi_conn_error(instance->conn, &errmsg);
		LOG_DEBUG_TRACE("dbi_errno: [ %d ], errmsg: [ %s ]\n", dbi_errno, errmsg);
	}
}*/

/*
* 函数: dbi_get_errno
* 功能: 获取当前错误代码
* 参数: obj		对象实例
* 返回: int		错误码
*		- 0		表示未发现错误
* 说明: 
*/
const int dbi_get_errno(dbi_object_t obj)
{
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		return dbi_conn_error(instance->conn, &errmsg);
	}

	return 0;
}

/*
* 函数: dbi_get_errmsg
* 功能: 获取当前错误信息
* 参数: obj		对象实例
* 返回: 错误信息指针
*		- NULL	无错误信息
* 说明: 
*/
const char *dbi_get_errmsg(dbi_object_t obj)
{
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		dbi_conn_error(instance->conn, &errmsg);
	}

	return errmsg;
}

