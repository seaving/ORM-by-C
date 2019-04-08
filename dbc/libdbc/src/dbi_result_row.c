#include "sys_inc.h"
#include "log_trace.h"
#include "asprintf.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* 函数: dbi_result_get_currow_idx
* 功能: 获取当前结果集合中的当前行
* 参数: result		结果集合
* 返回: unsigned long long	行数
*		- 0 查询失败
* 说明: 结果集合行数是从1开始的
*/
unsigned long long dbi_result_get_currow_idx(dbi_results_t result)
{
	if (result)
	{
		return dbi_result_get_currow(result);
	}

	return 0;
}

/*
* 函数: dbi_result_get_rows_count
* 功能: 获取当前结果集合中总行数
* 参数: result		结果集合
* 返回: unsigned long long	行数
* 说明: 
*/
unsigned long long dbi_result_get_rows_count(dbi_results_t result)
{
	if (result)
	{
		return dbi_result_get_numrows(result);
	}

	return 0;
}

/*
* 函数: dbi_result_row_seek
* 功能: 结果集合偏移
* 参数: result		结果集合
*		offset		偏移量
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 偏移基准是从当前位置进行offset偏移
*/
bool dbi_result_row_seek(dbi_results_t result, unsigned long long offset)
{
	if (result)
	{
		return (bool) dbi_result_seek_row(result, offset);
	}

	return false;
}

/*
* 函数: dbi_result_row_seek_to_first
* 功能: 结果集合偏移到第一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_first(dbi_results_t result)
{
	if (result)
	{
		return (bool) dbi_result_first_row(result);
	}

	return false;
}

/*
* 函数: dbi_result_row_seek_to_last
* 功能: 结果集合偏移到最后一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_last(dbi_results_t result)
{
	if (result)
	{
		return (bool) dbi_result_last_row(result);
	}

	return false;
}

/*
* 函数: dbi_result_row_seek_to_prev
* 功能: 结果集合偏移到前一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_prev(dbi_results_t result)
{
	if (result)
	{
		return (bool) dbi_result_prev_row(result);
	}

	return false;
}

/*
* 函数: dbi_result_row_seek_to_next
* 功能: 结果集合偏移到下一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_next(dbi_results_t result)
{
	if (result)
	{
		return (bool) dbi_result_next_row(result);
	}

	return false;
}

/*
* 函数: dbi_result_row_add
* 功能: 在result结果集合中增加一行
* 参数: result	结果集合
*		fmt 	格式化字符串，类似printf函数格式
*		... 	格式化参数列表
* 返回: bool
*		- false 失败
* 说明: fmt 格式: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt字符串中必须是[字段名.格式化标识]，多个字段之间用空格隔开
*		举例: dbi_result_row_add(row, "name.%s sex.%s age.%d", name, sex, age)
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
bool dbi_result_row_add(
	dbi_results_t result, const char *fmt, ...)
{
	const char *temp = fmt;
	int arg_len = 0;
	unsigned int ret = 0;
	va_list ap;
	
	if (result && fmt)
	{
		for ( ; temp && *temp != '\0'; )
		{
			temp = strchr(temp, '.');
			if (temp)
			{
				temp ++;
				arg_len ++;
			}
		}
		
		if (arg_len > 0)
		{
			va_start(ap, fmt);
			ret = dbi_result_field_bindf2(result, fmt, ap);
			va_end(ap);
			if (arg_len == ret)
			{
				return true;
			}
		}
	}
	
	return false;
}

