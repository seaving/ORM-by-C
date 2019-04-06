#ifndef __DBI_QUERY_H__
#define __DBI_QUERY_H__

#include "dbi_object.h"

/*
* 函数: dbi_query
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
*		sql		sql语句字符串
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: 
*/
dbi_results_t dbi_query(dbi_object_t obj, const char *sql);

/*
* 函数: dbi_query_by_statement_buf
* 功能: 执行sql语句并返回结果
* 参数: obj		dbi对象
* 返回: dbi_results_t	结果集合
*		- NULL 执行失败
* 说明: sql语句来源于obj成员statement
*/
dbi_results_t dbi_query_by_statement_buf(dbi_object_t obj);

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
dbi_results_t dbi_queryf(dbi_object_t obj, const char *fmt, ...);

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
dbi_results_t dbi_queryf2(dbi_object_t obj, const char *sql_fmt, va_list args);

/*
* 函数: dbi_query_db_list
* 功能: 查询数据库列表
* 参数: obj		dbi对象
*		pattern	SQL正则表达式，为空则查询所有可用
* 返回: dbi_results_t	结果集合
*		- NULL 查询失败
* 说明: 
*/
dbi_results_t dbi_query_db_list(dbi_object_t obj, const char *pattern);

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
	const char *db, const char *pattern);

/*
* 函数: dbi_switches_db
* 功能: 切换数据库
* 参数: obj		dbi对象
*		db		数据库
* 返回: bool
*		- false 失败
* 说明: 
*/
bool dbi_switches_db(dbi_object_t obj, const char *db);

#endif

