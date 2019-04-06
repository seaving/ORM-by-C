#include "includes.h"

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
			break;
	}
	
	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
}


