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

#include "dbc.h"

extern dbc_t sqlite3;

#endif

