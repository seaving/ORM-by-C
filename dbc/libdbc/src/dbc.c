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
* 函数: _dbc_exec
* 功能: 执行sql
* 参数: obj 			对象实例
*		sql_fmt 		sql语句字符串
*		... 			格式化参数列表
* 返回: bool
*		- false 失败
* 说明: 直接用来执行sql语句的方法
*/
static bool _dbc_exec(dbi_object_t obj, const char *sql_fmt, ...)
{
	dbi_results_t result = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| sql_fmt == NULL)
	{
		return false;
	}

	va_start(ap, sql_fmt);
	result = dbi_queryf2(obj, sql_fmt, ap);
	va_end(ap);

	return result ? true : false;
}

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
* 函数: _dbc_result_get_char
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: char
* 说明: 
*/
static char _dbc_result_get_char(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_char_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_uchar
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: unsigned char
* 说明: 
*/
static unsigned char _dbc_result_get_uchar(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uchar_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_short
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: short
* 说明: 
*/
static short _dbc_result_get_short(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_short_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_ushort
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: unsigned short
* 说明: 
*/
static unsigned short _dbc_result_get_ushort(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ushort_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_int
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: int
* 说明: 
*/
static int _dbc_result_get_int(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_int_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_uint
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: unsigned int
* 说明: 
*/
static unsigned int _dbc_result_get_uint(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uint_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_long
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: long
* 说明: 
*/
static long _dbc_result_get_long(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_long_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_ulong
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: unsigned long
* 说明: 
*/
static unsigned long _dbc_result_get_ulong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulong_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_longlong
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: long long
* 说明: 
*/
static long long _dbc_result_get_longlong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_longlong_value_by_fieldname(results, field);
	}

	return 0L;
}

/*
* 函数: _dbc_result_get_ulonglong
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: unsigned long long
* 说明: 
*/
static unsigned long long _dbc_result_get_ulonglong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulonglong_value_by_fieldname(results, field);
	}

	return 0L;
}

/*
* 函数: _dbc_result_get_float
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: float
* 说明: 
*/
static float _dbc_result_get_float(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_float_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_double
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: double
* 说明: 
*/
static double _dbc_result_get_double(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_double_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_string
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: const char *
* 说明: 
*/
static const char *_dbc_result_get_string(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_string_value_by_fieldname(results, field);
	}

	return NULL;
}

/*
* 函数: _dbc_result_get_binary
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: const unsigned char *
* 说明: 
*/
static const unsigned char *_dbc_result_get_binary(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_binary_value_by_fieldname(results, field);
	}

	return NULL;
}

/*
* 函数: _dbc_result_get_datetime
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		field	字段名
* 返回: time_t
* 说明: 
*/
static time_t _dbc_result_get_datetime(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_datetime_value_by_fieldname(results, field);
	}

	return 0;
}


/*
* 函数: _dbc_result_get_char_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: char
* 说明: 
*/
static char _dbc_result_get_char_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_char_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_uchar_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: unsigned char
* 说明: 
*/
static unsigned char _dbc_result_get_uchar_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uchar_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_short_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: short
* 说明: 
*/
static short _dbc_result_get_short_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_short_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_ushort_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: unsigned short
* 说明: 
*/
static unsigned short _dbc_result_get_ushort_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ushort_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_int_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: int
* 说明: 
*/
static int _dbc_result_get_int_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_int_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_uint_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: unsigned int
* 说明: 
*/
static unsigned int _dbc_result_get_uint_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uint_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_long_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: long
* 说明: 
*/
static long _dbc_result_get_long_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_long_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_ulong_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: unsigned long
* 说明: 
*/
static unsigned long _dbc_result_get_ulong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulong_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_longlong_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: long long
* 说明: 
*/
static long long _dbc_result_get_longlong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_longlong_value_by_idx(results, columnidx);
	}

	return 0L;
}

/*
* 函数: _dbc_result_get_ulonglong_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: unsigned long long
* 说明: 
*/
static unsigned long long _dbc_result_get_ulonglong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulonglong_value_by_idx(results, columnidx);
	}

	return 0L;
}

/*
* 函数: _dbc_result_get_float_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: float
* 说明: 
*/
static float _dbc_result_get_float_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_float_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_double_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: double
* 说明: 
*/
static double _dbc_result_get_double_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_double_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* 函数: _dbc_result_get_string_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: const char *
* 说明: 
*/
static const char *_dbc_result_get_string_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_string_value_by_idx(results, columnidx);
	}

	return NULL;
}

/*
* 函数: _dbc_result_get_binary_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: const unsigned char *
* 说明: 
*/
static const unsigned char *_dbc_result_get_binary_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_binary_value_by_idx(results, columnidx);
	}

	return NULL;
}

/*
* 函数: _dbc_result_get_datetime_by_colidx
* 功能: 在row中批量获取字段的值
* 参数: obj 	dbi object
*		rowidx	第几行，从1开始
*		columnidx	列号，从1开始
* 返回: time_t
* 说明: 
*/
static time_t _dbc_result_get_datetime_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_datetime_value_by_idx(results, columnidx);
	}

	return 0;
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
#define set_fun(c, f) \
	do { \
		if (c == NULL) \
		{ \
			c = f; \
		} \
	} while (0)

	set_fun(dbc.exec, _dbc_exec);

	set_fun(dbc.result.gets, _dbc_result_gets);

	set_fun(dbc.result.get_char, _dbc_result_get_char);
	set_fun(dbc.result.get_uchar, _dbc_result_get_uchar);
	set_fun(dbc.result.get_short, _dbc_result_get_short);
	set_fun(dbc.result.get_ushort, _dbc_result_get_ushort);
	set_fun(dbc.result.get_int, _dbc_result_get_int);
	set_fun(dbc.result.get_uint, _dbc_result_get_uint);
	set_fun(dbc.result.get_long, _dbc_result_get_long);
	set_fun(dbc.result.get_ulong, _dbc_result_get_ulong);
	set_fun(dbc.result.get_longlong, _dbc_result_get_longlong);
	set_fun(dbc.result.get_ulonglong, _dbc_result_get_ulonglong);
	set_fun(dbc.result.get_float, _dbc_result_get_float);
	set_fun(dbc.result.get_double, _dbc_result_get_double);
	set_fun(dbc.result.get_string, _dbc_result_get_string);
	set_fun(dbc.result.get_binary, _dbc_result_get_binary);
	set_fun(dbc.result.get_datetime, _dbc_result_get_datetime);

	set_fun(dbc.result.get_char_by_colidx, _dbc_result_get_char_by_colidx);
	set_fun(dbc.result.get_uchar_by_colidx, _dbc_result_get_uchar_by_colidx);
	set_fun(dbc.result.get_short_by_colidx, _dbc_result_get_short_by_colidx);
	set_fun(dbc.result.get_ushort_by_colidx, _dbc_result_get_ushort_by_colidx);
	set_fun(dbc.result.get_int_by_colidx, _dbc_result_get_int_by_colidx);
	set_fun(dbc.result.get_uint_by_colidx, _dbc_result_get_uint_by_colidx);
	set_fun(dbc.result.get_long_by_colidx, _dbc_result_get_long_by_colidx);
	set_fun(dbc.result.get_ulong_by_colidx, _dbc_result_get_ulong_by_colidx);
	set_fun(dbc.result.get_longlong_by_colidx, _dbc_result_get_longlong_by_colidx);
	set_fun(dbc.result.get_ulonglong_by_colidx, _dbc_result_get_ulonglong_by_colidx);
	set_fun(dbc.result.get_float_by_colidx, _dbc_result_get_float_by_colidx);
	set_fun(dbc.result.get_double_by_colidx, _dbc_result_get_double_by_colidx);
	set_fun(dbc.result.get_string_by_colidx, _dbc_result_get_string_by_colidx);
	set_fun(dbc.result.get_binary_by_colidx, _dbc_result_get_binary_by_colidx);
	set_fun(dbc.result.get_datetime_by_colidx, _dbc_result_get_datetime_by_colidx);
	
	set_fun(dbc.result.count, _dbc_result_count);

	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
#undef set_fun
}

