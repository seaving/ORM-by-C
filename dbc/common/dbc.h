/********************************************************************************
* @File name: dbc.h
* @Author: caixiwen
* @Date: 2019-4-6
* @Description: The function interface
*

dbc(database container数据库容器)，各种类型数据库的操作都被封装到此，使用者统一用
dbc来操作数据库，无须强调内部使用的是何种数据库

     app
      |
     dbc
      |
sqlite3 mysql ...
      |
  dbi object
      |
    libdbi
********************************************************************************/
#ifndef __DBC_H__
#define __DBC_H__

typedef intptr_t dbi_object_t;
/******************************************************************************/

typedef enum __dbc_sql_type__
{
	E_DBC_SQL_TYPE_SQLITE = 0,
	E_DBC_SQL_TYPE_SQLITE3,
	E_DBC_SQL_TYPE_MYSQL,
	E_DBC_SQL_TYPE_UNKOWN
} dbc_sql_type_t;

typedef struct __dbc_sql_args_
{
	dbc_sql_type_t sqltype;
	const char *hostname;
	const char *username;
	const char *password;
	const char *dbdir;
	const char *dbname;
	const char *encoding;
	const char *version;
} dbc_sql_args_t;
/******************************************************************************/
typedef struct __dbc_result__
{
	/*
	* 函数: gets
	* 功能: 在row中批量获取字段的值
	* 参数: obj		dbi object
	*		rowidx	第几行，从1开始
	*		fmt 	格式化字符串，类似printf函数格式
	*		args	格式化参数列表，用于保存获取到的值
	* 返回: unsigned int	获取成功字段数量
	*		- 0 			失败
	* 说明: fmt 格式: "fieldname1.%ul fieldname2.%s fieldname3.%s"
	*				fmt字符串中必须是[字段名.格式化标识]，多个字段之间用空格隔开
	*		... 为可变参数，每个参数传参必须加上取地址符号 &
	*		举例: gets(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
	unsigned int (*gets)(dbi_object_t obj, 
				unsigned int rowidx, const char *fmt, ...);

	/*
	* 函数: count
	* 功能: 获取当前结果集合中总行数
	* 参数: obj			dbi 对象
	* 返回: unsigned long long	行数
	* 说明: 
	*/
	unsigned long long (*count)(dbi_object_t obj);

} dbc_result_t;
/******************************************************************************/
typedef struct __dbc_filter__
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
} dbc_filter_t;
/******************************************************************************/
typedef struct __dbc__
{
	//-------------------------------------
	dbc_result_t result;
	dbc_filter_t filter;
	//-------------------------------------
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
} dbc_t;
/******************************************************************************/

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
dbc_t dbc_connect(dbi_object_t obj, dbc_sql_args_t args);

/*
* 函数: dbi_object_new
* 功能: 创建对象实例
* 参数: 无
* 返回: dbi对象
*		- 0		失败
* 说明: 
*/
extern dbi_object_t dbi_object_new();

/*
* 函数: dbi_object_delete
* 功能: 销毁对象实例
* 参数: obj		dbi对象
* 返回: 无
* 说明: 
*/
extern void dbi_object_delete(dbi_object_t obj);

#endif


