#ifndef __DBI_CONNECT_H__
#define __DBI_CONNECT_H__

#include "dbi_object.h"

/*
* 函数: dbi_connect_mysql_init
* 功能: 连接mysql数据库之前需要填充一些参数
* 参数: obj		对象实例
*		hostname	数据库主机地址
*		username	数据库用户名
*		password	数据库密码
*		dbname		数据库名称
*		encoding	编码
* 返回: 无
* 说明: 
*/
void dbi_connect_mysql_init(
	dbi_object_t obj, const char *hostname, 
	const char *username, const char *password, 
	const char *dbname, const char *encoding);

/*
* 函数: dbi_connect_sqlite_init
* 功能: 连接sqlite数据库之前需要填充一些参数
* 参数: obj		对象实例
*		dbdir	sqlite数据库路径
*		dbname	sqlite数据库名称
* 返回: 无
* 说明: 
*/
void dbi_connect_sqlite_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname);

/*
* 函数: dbi_connect_sqlite3_init
* 功能: 连接sqlite3数据库之前需要填充一些参数
* 参数: obj		对象实例
*		dbdir	sqlite数据库路径
*		dbname	sqlite数据库名称
* 返回: 无
* 说明: 
*/
void dbi_connect_sqlite3_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname);

/*
* 函数: dbi_connect
* 功能: 通过dbi object连接数据库
* 参数: obj			dbi对象
*		sql_name	数据库类型 - mysql postgresql sqlite3
*		host		数据库主机地址
*		username	数据库用户名
*		password	数据库密码
*		dbname		数据库名称
*		encoding	编码
* 返回: bool
*		- false 失败
*		- true 成功
* 说明: 在调用dbi_connect之前请务必先调用相应的sql conect初始化函数
*		e.g. 
*			- dbi_connect_mysql_init
*			- dbi_connect_sqlite_init
*			- dbi_connect_sqlite3_init
*/
bool dbi_connect(dbi_object_t obj);

/*
* 函数: dbi_disconnect
* 功能: 通过dbi object断开连接数据库
* 参数: obj			dbi对象
* 返回: bool
*		- false 失败
*		- true 成功
* 说明: 
*/
bool dbi_disconnect(dbi_object_t obj);

/*
* 函数: dbi_connection_is_alive
* 功能: 判断连接是否正常
* 参数: obj		dbi对象
* 返回: bool
*		- false 连接可能断开
*		- true	连接正常
* 说明: 多ping几次提高准确率
*/
bool dbi_connection_is_alive(dbi_object_t obj);

#endif


