#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

#include "sql_sqlite3.h"

/*
* 函数: _dbc_result_gets
* 功能: 在row中批量获取字段的值
* 参数: obj		dbi object
*		rowidx	第几行，从1开始
*		fmt 	格式化字符串，类似printf函数格式
*		args 	格式化参数列表，用于保存获取到的值
* 返回: unsigned int	获取成功字段数量
*		- 0 			失败
* 说明: fmt 格式: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt字符串中必须是[字段名.格式化标识]，多个字段之间用空格隔开
*		... 为可变参数，每个参数传参必须加上取地址符号 &
*		举例: _dbc_result_gets(row, "name.%s sex.%s age.%d", &name, &sex, &age)
*	--- 格式字符:
*		%c / %uc: char / unsigned char
*		%h / %uh: short / unsigned short
*		%l / %ul: int / unsigned int(long与int一样)
*		%i / %ui: int / unsigned int(long与int一样)
*		%L / %uL: long long / unsigned long long
*		%f: float
*		%d: double
*		%s: string
*		%b: unsigned char * 二进制字符串
*		%t: time_t 表示日期和/或时间的时间值
*/
static unsigned int _dbc_result_gets(
	dbi_object_t obj, unsigned int rowidx, const char *fmt, ...)
{
	unsigned int ret = 0;
	va_list ap;
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| fmt == NULL)
	{
		return 0;
	}

	va_start(ap, fmt);
	dbi_result_row_seek(results, rowidx);
	ret = dbi_result_field_get_values2(results, fmt, ap);
	va_end(ap);
	return ret;
}

/*
* 函数: _dbc_result_count
* 功能: 获取当前结果集合中总行数
* 参数: obj			dbi 对象
* 返回: unsigned long long	行数
* 说明: 
*/
static unsigned long long _dbc_result_count(dbi_object_t obj)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL)
	{
		return 0;
	}

	return dbi_result_get_rows_count(results);
}

/*
* 函数: dbc_connect
* 功能: 连接数据库
* 参数: obj		对象实例
*		args	一些数据库相关的参数，比如连接数据库需要的参数
* 返回: dbc_t	返回一个dbc对象
* 说明: args结构体里面的参数并非所有都要赋值，针对数据库不同，所需参数也不同
*		比如mysql数据库用到的是username password hostname，而sqlite3用到的则
*		是dbdir和dbname
*		使用方法:
*			以sqlite3为例:
*			dbc_sql_args_t sql_args = {.dbdir="", .dbname=""};
*			dbc_connect(obj, sql_args);
*		直接定义一个args变量并且初始化值，再进行传参，不需要指针操作，
*		仅仅只是用来传递参数而已，这本是设计的初衷
*/
dbc_t dbc_connect(dbi_object_t obj, dbc_sql_args_t args)
{
	bool sqltype_flag = true;
	dbc_t dbc;

	memset(&dbc, 0, sizeof(dbc_t));
	
	switch (args.sqltype)
	{
		case E_DBC_SQL_TYPE_SQLITE:
			//dbc = sqlite;
			//dbi_connect_sqlite_init(obj, args.dbdir, args.dbname);
			//break;
		case E_DBC_SQL_TYPE_SQLITE3:
			dbc = sqlite3;
			dbi_connect_sqlite3_init(obj, args.dbdir, args.dbname);
			break;
		case E_DBC_SQL_TYPE_MYSQL:
			//dbc = mysql;
			//dbi_connect_mysql_init(
			//	obj, args.hostname, args.username, 
			//	args.password, args.dbname, args.encoding);
		default:
			LOG_TRACE("Not support SQL: %d\n", args.sqltype);
			sqltype_flag = false;
			break;
	}
	
	if (sqltype_flag == false)
	{
		return dbc;
	}

	dbc.result.gets = _dbc_result_gets;
	dbc.result.count = _dbc_result_count;
	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
}

