/********************************************************************************
* @File name: sql_sqlite3.h
* @Author: caixiwen
* @Date: 2019-4-6
* @Description: The function interface
*

对外层: sql_sqlite3_t	通过结构体方法对外开放API，类似于C++中namespace或class封装起来
中间层: sql_sqlite3.c	提供数据库语句的构造封装，为每一个数据库操作(insert, select
						delete, update等)结合过滤器(and or limit order by等)进行语句的重组
						最终调用query方法执行
底层: 	dbi_object		封装了对大部分数据库的api，对外统一接口
********************************************************************************/

#ifndef __SQL_SQLITE_3_H__
#define __SQL_SQLITE_3_H__

#include "dbi_object.h"

/******************************************************************************/
typedef struct __sql_sqlite3_filter__
{
	/*
	* 函数: and
	* 功能: 构造条件，sql语句中的AND条件
	*		该函数自动会把AND加上，不需要用户处理
	*		用户只需要按照字符串的形式把条件传参
	* 参数: obj 			对象实例
	*		condition_fmt 	条件语句格式化
	*		... 			参数列表
	* 返回: bool
	*		- false 失败
	* 说明: 规定condition只能是一个判断语句
	*	e.g. and(obj, "name != 'jorry'")
	*	e.g. and(obj, "age > 20")
	*	e.g. and(obj, "age == %d", age)
	*/
	bool (*and)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* 函数: or
	* 功能: 构造条件，sql语句中的OR条件
	*		该函数自动会把OR加上，不需要用户处理
	*		用户只需要按照字符串的形式把条件传参
	* 参数: obj 			对象实例
	*		condition_fmt 	条件语句格式化
	*		... 			参数列表
	* 返回: bool
	*		- false 失败
	* 说明: 规定condition只能是一个判断语句
	*	e.g. or(obj, "name != 'jorry'")
	*	e.g. or(obj, "age > 20")
	*	e.g. or(obj, "age == %d", age)
	*/
	bool (*or)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* 函数: limit
	* 功能: 构造条件，sql语句中的LIMIT OFFSET命令
	* 参数: obj 			对象实例
	*		offset 			偏移到第几行
	*		limit_ 			到offset+limit_行结束
	* 返回: bool
	*		- false 失败
	* 说明: 该函数结合select使用
	*/
	bool (*limit)(dbi_object_t obj, unsigned int offset, unsigned int limit_);
} sql_sqlite3_filter_t;
/******************************************************************************/
typedef struct __sql_sqlite3__
{
	sql_sqlite3_filter_t filter;
	//-------------------------------------
	/*
	* 函数: _sql_sqlite3_connect
	* 功能: 连接操作
	* 参数: obj 		对象实例
	*		dbdir		数据库路径
	*		dbname		数据库名称
	* 返回: bool
	*		- false 失败
	* 说明: 
	*/
	bool (*connect)(dbi_object_t obj, const char *dbdir, const char *dbname);
	/*
	* 函数: disconnect
	* 功能: 断开连接操作
	* 参数: obj 		对象实例
	* 返回: bool
	*		- false 失败
	* 说明: 
	*/
	bool (*disconnect)(dbi_object_t obj);
	/*
	* 函数: query
	* 功能: 执行sql
	* 参数: obj 			对象实例
	* 返回: bool
	*		- false 失败
	* 说明: 执行所有的insert，delete，update，select等sql操作函数后
	*		必须最终调用query来真正的让数据库引擎执行sql操作并且返回结果
	*/
	bool (*query)(dbi_object_t obj);
	/*
	* 函数: insert
	* 功能: 插入操作
	* 参数: obj 			对象实例
	*		tbname			表名
	*		fields			字段列表
	*		values_fmt		值列表
	*		... 			参数列表
	* 返回: bool
	*		- false 失败
	* 说明: 字段列表是字符串格式: "field1, field2, field3, field4" 用逗号隔开
	*		值列表是字符串格式: "value1, value2, value3, value4" 用逗号隔开
	*		值列表中如果有值是字符串，必须加上''号，要遵从sql语句格式
	*/
	bool (*insert)(dbi_object_t obj, const char *tbname, 
					const char *fields, const char *values_fmt, ...);
	/*
	* 函数: delete
	* 功能: 删除操作
	* 参数: obj 			对象实例
	*		tbname			表名
	* 返回: bool
	*		- false 失败
	* 说明: 结合filter中提供的方法构造条件
	*/
	bool (*delete)(dbi_object_t obj, const char *tbname);
	/*
	* 函数: update
	* 功能: 更新操作
	* 参数: obj 			对象实例
	*		tbname			表名称
	*		set_fmt			字段赋值格式化语句
	* 返回: bool
	*		- false 失败
	* 说明: 结合filter中提供的方法构造条件
	*		set_fmt 格式遵从sql语法，"field1=value1, field2='value2', field3='value3'"
	*/
	bool (*update)(dbi_object_t obj, const char *tbname, const char *set_fmt);
	/*
	* 函数: select
	* 功能: 查询操作
	* 参数: obj 			对象实例
	*		tbname			表名称
	*		fields			要查询的字段，*号表示所有字段
	* 返回: bool
	*		- false 失败
	* 说明: 结合filter中提供的方法构造条件
	*		field 格式遵从sql语法，"field1, field2, field3"，用逗号隔开
	*/
	bool (*select)(dbi_object_t obj, const char *tbname, const char *fields);
} sql_sqlite3_t;
/******************************************************************************/

extern sql_sqlite3_t sqlite3;

#endif

