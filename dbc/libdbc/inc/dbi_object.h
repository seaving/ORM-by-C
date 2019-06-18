/********************************************************************************
* @File name: dbi_object.h
* @Author: caixiwen
* @Date: 2019-4-1
* @Description: The function interface
*

libdbi 需要先编译安装libdbi框架，再安装libdbi driver
在安装driver时候，需要安装数据库的lib文件
举例:
	sqlite3 driver安装:
		先安装libsqlite3，从官网下载最新的sqlite，编译安装
		其次到libdbi driver源码中执行 ./configure --with-sqlite3进行安装driver
		注意: sqlite3版本尽量选择新版本，老版本编译出来的sqlite库会缺少函数，不能
		与libdbi相匹配，导致无法加载driver
********************************************************************************/

#ifndef __DBI_OBJECT_H__
#define __DBI_OBJECT_H__

#include "sys_inc.h"

#define DBI_STATEMENT_BUF_SIZE	8 * 1024

typedef struct __dbi_instance__
{
	dbi_conn conn;
	dbi_result result;
	dbi_inst instance;

	char statement[DBI_STATEMENT_BUF_SIZE];

	char driverdir[256];
	char sql_name[64];
	char drivername[64];
	char hostname[256];
	char username[64];
	char password[64];
	char dbdir[256];
	char dbname[64];
	char encoding[20];
	char version[64];
	int query_log;

	pthread_mutex_t lock;
} dbi_instance_t;

typedef intptr_t dbi_object_t;
typedef dbi_result dbi_results_t;

#define DBI_OBJECT_NULL		(0)

/*
* 函数: dbi_object_new
* 功能: 创建对象实例
* 参数: 无
* 返回: dbi对象
*		- 0		失败
* 说明: 
*/
dbi_object_t dbi_object_new();

/*
* 函数: dbi_object_delete
* 功能: 销毁对象实例
* 参数: obj		dbi对象
* 返回: 无
* 说明: 
*/
void dbi_object_delete(dbi_object_t obj);

/*
* 函数: dbi_object_mutex_lock
* 功能: 互斥锁
* 参数: obj			dbi对象
* 返回: 无
* 说明: 
*/
void dbi_object_mutex_lock(dbi_object_t obj);

/*
* 函数: dbi_object_mutex_unlock
* 功能: 互斥锁
* 参数: obj			dbi对象
* 返回: 无
* 说明: 
*/
void dbi_object_mutex_unlock(dbi_object_t obj);

/*
* 函数: dbi_object_statement_compose
* 功能: 构造sql语句
* 参数: obj			dbi对象
*		statement	语句
* 返回: int		当前长度
* 说明: 
*/
int dbi_object_statement_compose(dbi_object_t obj, char *statement);

/*
* 函数: dbi_object_statement_composef
* 功能: 构造sql语句
* 参数: obj			dbi对象
*		fmt			格式化语句
*		...			参数列表
* 返回: int		当前长度
* 说明: 
*/
int dbi_object_statement_composef(dbi_object_t obj, char *fmt, ...);

/*
* 函数: dbi_object_statement_composef2
* 功能: 构造sql语句
* 参数: obj			dbi对象
*		fmt			格式化语句
*		args		参数列表
* 返回: int		当前长度
* 说明: 
*/
int dbi_object_statement_composef2(dbi_object_t obj, char *fmt, va_list args);

/*
* 函数: dbi_object_statement_clear_buf
* 功能: 获取sql语句buf的指针
* 参数: obj		dbi对象
* 返回: 无
* 说明: 
*/
void dbi_object_statement_clear_buf(dbi_object_t obj);

/*
* 函数: dbi_object_statement_debug
* 功能: 输出当前sql语句
* 参数: obj		dbi对象
* 返回: 无
* 说明: 
*/
void dbi_object_statement_debug(dbi_object_t obj);

/*
* 函数: dbi_object_statement_get_buf
* 功能: 获取sql语句buf的指针
* 参数: obj		dbi对象
* 返回: 无
* 说明: 
*/
char *dbi_object_statement_get_buf(dbi_object_t obj);

/*
* 函数: dbi_object_get_results
* 功能: 获取结果集
* 参数: obj		dbi对象
* 返回: dbi_results_t
*		- NULL	失败
* 说明: 
*/
dbi_results_t dbi_object_get_results(dbi_object_t obj);


#endif


