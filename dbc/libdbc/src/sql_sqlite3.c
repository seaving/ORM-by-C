#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/******************************************************************************/
static const char *_sql_sqlite3_fun_sum(const char *field);
static const char *_sql_sqlite3_fun_count(const char *field);
static const char *_sql_sqlite3_fun_distinct(const char *field);

static bool _sql_sqlite3_and(dbi_object_t obj, char *condition_fmt, ...);
static bool _sql_sqlite3_or(dbi_object_t obj, char *condition_fmt, ...);

static bool _sql_sqlite3_limit(dbi_object_t obj, 
						unsigned int offset, unsigned int limit);

static bool _sql_sqlite3_query(dbi_object_t obj);

static bool _sql_sqlite3_insert(dbi_object_t obj, const char *tbname, 
						const char *fields, const char *values_fmt, ...);

static bool _sql_sqlite3_delete(dbi_object_t obj, const char *tbname);

static bool _sql_sqlite3_update(dbi_object_t obj, 
						const char *tbname, const char *set_fmt);

static bool _sql_sqlite3_select(dbi_object_t obj, const char *tbname, 
						const char *field1, ...);
/******************************************************************************/
dbc_t sqlite3 = {
	.sql_fun = {
		.sum = _sql_sqlite3_fun_sum,
		.count = _sql_sqlite3_fun_count,
		.distinct = _sql_sqlite3_fun_distinct,
	},
	.filter = {
		.and = _sql_sqlite3_and,
		.or = _sql_sqlite3_or,
		.limit = _sql_sqlite3_limit,
	},
	.disconnect = dbi_disconnect,
	.query = _sql_sqlite3_query,
	.insert = _sql_sqlite3_insert,
	.delete = _sql_sqlite3_delete,
	.update = _sql_sqlite3_update,
	.select = _sql_sqlite3_select,
};
/******************************************************************************/
/*
* 函数: sum
* 功能: 汇总，本质也是构造字符串
* 参数: field		被统计的字段
* 返回: char *
*		- NULL		失败
* 说明: 配合select使用
*/
static const char *_sql_sqlite3_fun_sum(const char *field)
{
	static char str[256] = {0};
	snprintf(str, sizeof(str) - 1, "sum(%s)", field);
	return str;
}

/*
* 函数: count
* 功能: 统计数量，本质也是构造字符串
* 参数: field		被统计的字段
* 返回: char *
*		- NULL		失败
* 说明: 配合select使用
*/
static const char *_sql_sqlite3_fun_count(const char *field)
{
	static char str[256] = {0};
	snprintf(str, sizeof(str) - 1, "count(%s)", field);
	return str;
}

/*
* 函数: distinct
* 功能: 去重，本质也是构造字符串
* 参数: field		去重字段
* 返回: char *
*		- NULL		失败
* 说明: 配合select使用
*/
static const char *_sql_sqlite3_fun_distinct(const char *field)
{
	static char str[256] = {0};
	snprintf(str, sizeof(str) - 1, "DISTINCT %s", field);
	return str;
}
/******************************************************************************/

/*
* 函数: _sql_sqlite3_and
* 功能: 构造条件，sql语句中的AND条件
*		该函数自动会把AND加上，不需要用户处理
*		用户只需要按照字符串的形式把条件传参
* 参数: obj 			对象实例
*		condition_fmt	条件语句格式化
*		... 			参数列表
* 返回: bool
*		- false 失败
* 说明: 规定condition只能是一个判断语句
*	e.g. _sql_sqlite3_and(obj, "name != 'jorry'")
*	e.g. _sql_sqlite3_and(obj, "age > 20")
*	e.g. _sql_sqlite3_and(obj, "age == %d", age)
*/
static bool _sql_sqlite3_and(dbi_object_t obj, char *condition_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| condition_fmt == NULL)
	{
		return false;
	}

	len = strlen(condition_fmt);
	if (len <= 0)
	{
		return false;
	}
	
	len += 10;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}
	
	va_start(ap, condition_fmt);
	snprintf(sql, len, "AND %s", condition_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);

	return true;
}

/*
* 函数: _sql_sqlite3_or
* 功能: 构造条件，sql语句中的OR条件
*		该函数自动会把OR加上，不需要用户处理
*		用户只需要按照字符串的形式把条件传参
* 参数: obj 			对象实例
*		condition_fmt	条件语句格式化
*		... 			参数列表
* 返回: bool
*		- false 失败
* 说明: 规定condition只能是一个判断语句
*	e.g. _sql_sqlite3_or(obj, "name != 'jorry'")
*	e.g. _sql_sqlite3_or(obj, "age > 20")
*	e.g. _sql_sqlite3_or(obj, "age == %d", age)
*/
static bool _sql_sqlite3_or(dbi_object_t obj, char *condition_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| condition_fmt == NULL)
	{
		return false;
	}
	
	len = strlen(condition_fmt);
	if (len <= 0)
	{
		return false;
	}
	len += 10;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}

	va_start(ap, condition_fmt);
	snprintf(sql, len, "OR %s", condition_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);
	
	return true;
}
/*
* 函数: _sql_sqlite3_limit
* 功能: 构造条件，sql语句中的LIMIT OFFSET命令
* 参数: obj 			对象实例
*		offset			偏移到第几行
*		limit_			到offset+limit_行结束
* 返回: bool
*		- false 失败
* 说明: 该函数结合select使用
*/
static bool _sql_sqlite3_limit(dbi_object_t obj, 
	unsigned int offset, unsigned int limit)
{
	if (obj == DBI_OBJECT_NULL)
	{
		return false;
	}

	dbi_object_statement_composef(obj, "LIMIT %u OFFSET %u", limit, offset);
	return true;
}

/******************************************************************************/
/*
* 函数: _sql_sqlite3_query
* 功能: 执行sql
* 参数: obj 			对象实例
* 返回: bool
*		- false 失败
* 说明: 执行所有的insert，delete，update，select等sql操作函数后
*		必须最终调用query来真正的让数据库引擎执行sql操作并且返回结果
*/
static bool _sql_sqlite3_query(dbi_object_t obj)
{
	if (obj == DBI_OBJECT_NULL)
	{
		return false;
	}

	if (dbi_query_by_statement_buf(obj) == false)
	{
		dbi_error_debug(obj);
		return false;
	}

	return true;
}
/******************************************************************************/
/*
* 函数: _sql_sqlite3_insert
* 功能: 插入操作
* 参数: obj 			对象实例
*		tbname			表名
*		fields			字段列表
*		values_fmt		值列表
*		...				参数列表
* 返回: bool
*		- false 失败
* 说明: 字段列表是字符串格式: "field1, field2, field3, field4" 用逗号隔开
*		值列表是字符串格式: "value1, value2, value3, value4" 用逗号隔开
*		值列表中如果有值是字符串，必须加上''号，要遵从sql语句格式
*/
static bool _sql_sqlite3_insert(
	dbi_object_t obj, const char *tbname, 
	const char *fields, const char *values_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL
		|| tbname == NULL 
		|| fields == NULL 
		|| values_fmt == NULL)
	{
		return false;
	}
	
	len = strlen(fields) + strlen(values_fmt);
	if (len <= 0)
	{
		return false;
	}
	
	len += 64;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}

	snprintf(sql, len, 
		"INSERT INTO %s (%s) VALUES (%s)", 
		tbname, fields, values_fmt);

	va_start(ap, values_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);

	return true;
}

/*
* 函数: _sql_sqlite3_delete
* 功能: 更新操作
* 参数: obj 			对象实例
*		tbname			表名称
*		set_fmt 		字段赋值格式化语句
* 返回: bool
*		- false 失败
* 说明: 结合filter中提供的方法构造条件
*		set_fmt 格式遵从sql语法，"field1=value1, field2='value2', field3='value3'"
*/
static bool _sql_sqlite3_delete(
	dbi_object_t obj, const char *tbname)
{
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL)
	{
		return false;
	}

	dbi_object_statement_composef(obj, "DELETE FROM %s WHERE 1=1", tbname);
	return true;
}

/*
* 函数: _sql_sqlite3_update
* 功能: 更新数据
* 参数: obj				对象实例
*		tbname			表名称
*		set_fmt			字段赋值格式化语句
* 返回: bool
*		- false 失败
* 说明: set_fmt遵从sql语法
*/
static bool _sql_sqlite3_update(
	dbi_object_t obj, const char *tbname, 
	const char *set_fmt)
{
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL)
	{
		return false;
	}

	dbi_object_statement_composef(
		obj, "UPDATE %s SET %s WHERE 1=1", 
			tbname, set_fmt);

	return true;
}

/*
* 函数: _sql_sqlite3_select
* 功能: 查询操作
* 参数: obj 			对象实例
*		tbname			表名称
*		field1			要查询的字段，*号表示所有字段
*		...				字段列表
* 返回: bool
*		- false 失败
* 说明: 结合filter中提供的方法构造条件
*		可变参数列表必须以NULL结尾，否则程序会内存溢出
*		_sql_sqlite3_select(obj, taname, "field1", "field2", "count(name)", NULL);
*/
static bool _sql_sqlite3_select(
	dbi_object_t obj, const char *tbname, 
	const char *field1, ...)
{
	int i = 0;
	int cnt = 0;
	int offset = 0;
	int len = 0;
	const char *field = NULL;
	char *fields = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL
		|| field1 == NULL)
	{
		return false;
	}

	va_start(ap, field1);
	len += strlen(field1) + 1 + 1; // 一个逗号 一个空格
	for (cnt = 1; (field = va_arg(ap, const char *)) != NULL; cnt ++)
	{
		len += strlen(field) + 1 + 1;
	}
	va_end(ap);

	fields = calloc(1, len + 1);
	if (fields == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}

	va_start(ap, field1);
	offset = snprintf(fields, len - offset, 
				"%s%s", field1, cnt > 1 ? ", " : " ");
	for (i = 1; i < cnt - 1; i ++)
	{
		offset = snprintf(fields + offset, 
					len - offset, "%s, ", va_arg(ap, const char *));
	}
	offset = snprintf(fields + offset, 
				len - offset, "%s ", va_arg(ap, const char *));	
	va_end(ap);

	dbi_object_statement_composef(
		obj, "SELECT %s FROM %s WHERE 1=1", 
			fields, tbname);
	free(fields);
	
	return true;
}

