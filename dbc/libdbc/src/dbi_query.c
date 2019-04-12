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
* 函数: _dbi_result_free
* 功能: 回收dbi_result
* 参数: obj		对象实例
* 返回: 无
* 说明: 每次用完result一定要记得回收
*/
static inline void _dbi_result_free(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->result)
	{
		dbi_result_free(instance->result);
		instance->result = NULL;
	}
}

/*
* 函数: dbi_query
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
*		sql		sql语句字符串
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: 
*/
dbi_results_t dbi_query(dbi_object_t obj, const char *sql)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	LOG_DEBUG_TRACE("---->>> %s\n\n", sql);

	_dbi_result_free(obj);
	instance->result = dbi_conn_query(instance->conn, sql);
	
	return instance->result;
}

/*
* 函数: dbi_query_by_statement_buf
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: sql语句来源于obj成员statement
*/
dbi_results_t dbi_query_by_statement_buf(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	LOG_DEBUG_TRACE("---->>> %s\n\n", instance->statement);
	
	_dbi_result_free(obj);
	instance->result = dbi_conn_query(instance->conn, instance->statement);
	dbi_object_statement_clear_buf(obj);
	
	return instance->result;
}

/*
* 函数: dbi_queryf
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
*		fmt		格式化字符串，类似printf
*		...		格式化参数列表
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: fmt和... 共同构造一个sql语句字符串
*/
dbi_results_t dbi_queryf(dbi_object_t obj, const char *sql_fmt, ...)
{
	dbi_results_t results = NULL;
	va_list ap;
	va_start(ap, sql_fmt);
	results = dbi_queryf2(obj, sql_fmt, ap);
	va_end(ap);

	return results;
}

/*
* 函数: dbi_queryf2
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
*		fmt		格式化字符串，类似printf
*		args	格式化参数列表
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: fmt和... 共同构造一个sql语句字符串
*		可以用于二级传参
*/
dbi_results_t dbi_queryf2(dbi_object_t obj, const char *sql_fmt, va_list args)
{
	char *sql = NULL;

	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	vasprintf(&sql, sql_fmt, args);
	_dbi_result_free(obj);
	if (sql)
	{
		LOG_DEBUG_TRACE("---->>> %s\n\n", sql);

		instance->result = dbi_conn_query(instance->conn, sql);
		free(sql);
	}

	return instance->result;
}

/*
* 函数: dbi_query_db_list
* 功能: 查询数据库列表
* 参数: obj		dbi对象
*		pattern	SQL正则表达式，为空则查询所有可用
* 返回: dbi_results_t	结果集合
*		- NULL 查询失败
* 说明: 
*/
dbi_results_t dbi_query_db_list(dbi_object_t obj, const char *pattern)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	_dbi_result_free(obj);
	instance->result = dbi_conn_get_db_list(instance->conn, pattern);

	return instance->result;
}

/*
* 函数: dbi_query_table_list
* 功能: 查询数据表列表
* 参数: obj		dbi对象
*		db		数据库
*		pattern	SQL正则表达式，为空则查询所有可用
* 返回: dbi_results_t	结果集合
*		- NULL 查询失败
* 说明: 
*/
dbi_results_t dbi_query_table_list(dbi_object_t obj, 
	const char *db, const char *pattern)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL 
		|| instance->conn == NULL 
		|| db == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : 
			db == NULL ? "db is null!" : "");
		return NULL;
	}

	_dbi_result_free(obj);
	instance->result = dbi_conn_get_table_list(instance->conn, db, pattern);

	return instance->result;
}

/*
* 函数: dbi_switches_db
* 功能: 切换数据库
* 参数: obj		dbi对象
*		db		数据库
* 返回: bool
*		- false 失败
* 说明: 
*/
bool dbi_switches_db(dbi_object_t obj, const char *db)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL 
		|| instance->conn == NULL 
		|| db == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : 
			db == NULL ? "db is null!" : "");
		return false;
	}

	return dbi_conn_select_db(instance->conn, db);
}




