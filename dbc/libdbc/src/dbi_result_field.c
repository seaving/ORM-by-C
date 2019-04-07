#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* 函数: bdi_result_parse_field_formatstr
* 功能: 解析format字符串
* 参数: 
* 返回: 
* 说明: 
*/
unsigned int bdi_parse_field_formatstr(
	const char *format, char ***tokens_dest, char ***fieldnames_dest)
{
	unsigned int found = 0;
	unsigned int cur = 0;
	char **tokens = NULL;
	char **fieldnames = NULL;
	char *chunk = NULL;
	char *fieldtype = NULL;
	char *fieldname = NULL;
	char *temp1 = NULL;
	char *temp2 = NULL;
	char *line = strdup(format);

	temp1 = line;
	while (temp1 && (temp1 = strchr(temp1, '.')) != NULL)
	{
		temp1 ++;
		found ++;
	}

	tokens = calloc(found, sizeof(char *));
	fieldnames = calloc(found, sizeof(char *));
	if (tokens == NULL 
		|| fieldnames == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return 0;
	}
	
	chunk = strtok_r(line, " ", &temp1);
	do {
		temp2 = strchr(chunk, '.');
		if (temp2 == NULL)
		{
			continue;
		}
		
		fieldname = chunk;
		*temp2 = '\0';
		
		/* ignore the % */
		fieldtype = (temp2 + 2);
		tokens[cur] = strdup(fieldtype);
		fieldnames[cur] = strdup(fieldname);
		cur ++;
	} while ((chunk = strtok_r(NULL, " ", &temp1)));

	*tokens_dest = tokens;
	*fieldnames_dest = fieldnames;

	free(line);
	return found;
}

/*
* 函数: dbi_free_string_list
* 功能: 
* 参数: 
* 返回: 
* 说明: 
*/
void dbi_free_string_list(char **ptrs, int total)
{
	int i = 0;

	if (ptrs)
	{
		for (i = 0; i < total; ++ i)
		{
			if (ptrs[i])
			{
				free(ptrs[i]);
			}
		}
		free(ptrs);
	}
}

/*
* 函数: dbi_result_field_get_length_by_fieldname
* 功能: 通过fieldname获取该字段内容的长度
* 参数: row		结果集合的行
* 返回: size_t
* 说明: 对于字符串或者二进制字符串以外的字段类型的内容长度返回0
*		例如 Int型的字段内容长度则返回0
*/
size_t dbi_result_field_get_length_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_field_length(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_length_by_idx
* 功能: 通过序列号获取该字段的长度
* 参数: row		结果集合的行
*		idx		该行的第几列，序号是从1开始的
* 返回: size_t
* 说明: 序列号是从1开始的
*		对于字符串或者二进制字符串以外的字段类型的内容长度返回0
*		例如 Int型的字段内容长度则返回0
*/
size_t dbi_result_field_get_length_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_field_length_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_idx
* 功能: 查询字段在row中的序号
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned int
*		- > 0	该字段的序号
*		- = 0	错误
* 说明: 序列号是从1开始的
*/
unsigned int dbi_result_field_get_idx(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_field_idx(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_name
* 功能: 在row中查询指定序号的字段名称
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: const char *
*		- NULL		查询失败
* 说明: 序列号是从1开始的
*/
const char *dbi_result_field_get_name(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_field_name(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_count
* 功能: 在row中统计字段数量
* 参数: row			结果集合的行
* 返回: unsigned int
*		- 0			失败
* 说明: 
*/
unsigned int dbi_result_field_get_count(dbi_results_t row)
{
	if (row)
	{
		return dbi_result_get_numfields(row);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_type_by_fieldname
* 功能: 在row中指定字段的类型
* 参数: row			结果集合的行
*		fieldname	字段名
* 返回: unsigned short
*		- 0			失败
* 说明: 
*/
unsigned short dbi_result_field_get_type_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_field_type(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_field_get_type_by_idx
* 功能: 在row中指定字段的类型
* 参数: row			结果集合的行
*		idx			序号，需要从1开始
* 返回: unsigned short
*		- 0			失败
* 说明: 
*/
unsigned short dbi_result_field_get_type_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_field_type_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_field_is_null_value_by_fieldname
* 功能: 在row中指定字段的值是否为空
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: bool
*		- false		失败
*		- true		为空
* 说明: 
*/
bool dbi_result_field_is_null_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return (bool) dbi_result_field_is_null(row, fieldname);
	}

	return false;
}

/*
* 函数: dbi_result_field_is_null_value_by_idx
* 功能: 在row中指定字段的值是否为空
* 参数: row			结果集合的行
*		idx			序号，需要从1开始
* 返回: bool
*		- false		失败
*		- true		为空
* 说明: 
*/
bool dbi_result_field_is_null_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return (bool) dbi_result_field_is_null_idx(row, idx);
	}

	return false;
}

/*
* 函数: dbi_result_get_char_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: char
*		- 0		失败
* 说明: 
*/
char dbi_result_get_char_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_char(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_uchar_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned char
*		- 0		失败
* 说明: 
*/
unsigned char dbi_result_get_uchar_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_uchar(row, fieldname);
	}

	return 0;
}


/*
* 函数: dbi_result_get_short_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: short
*		- 0			失败
* 说明: 
*/
short dbi_result_get_short_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_short(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_ushort_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned short
*		- 0			失败
* 说明: 
*/
unsigned short dbi_result_get_ushort_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_ushort(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_int_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: int
*		- 0		失败
* 说明: 
*/
int dbi_result_get_int_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_int(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_uint_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned int
*		- 0			失败
* 说明: 
*/
unsigned int dbi_result_get_uint_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_uint(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_long_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: int
*		- 0			失败
* 说明: 
*/
int dbi_result_get_long_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	return dbi_result_get_int_value_by_fieldname(row, fieldname);
}

/*
* 函数: dbi_result_get_ulong_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned int
*		- 0			失败
* 说明: 
*/
unsigned int dbi_result_get_ulong_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	return dbi_result_get_uint_value_by_fieldname(row, fieldname);
}

/*
* 函数: dbi_result_get_longlong_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: long long
*		- 0			失败
* 说明: 
*/
long long dbi_result_get_longlong_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_longlong(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_ulonglong_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: unsigned long long
*		- 0			失败
* 说明: 
*/
unsigned long long dbi_result_get_ulonglong_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_ulonglong(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_float_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: float
*		- 0			失败
* 说明: 
*/
float dbi_result_get_float_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_float(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_double_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: double
*		- 0			失败
* 说明: 
*/
double dbi_result_get_double_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_double(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_string_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: const char *
*		- NULL		失败
* 说明: 
*/
const char *dbi_result_get_string_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_string(row, fieldname);
	}

	return NULL;
}

/*
* 函数: dbi_result_get_binary_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: const unsigned char *
*		- NULL		失败
* 说明: 
*/
const unsigned char *dbi_result_get_binary_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	size_t length = 0;
	if (row && fieldname)
	{
		length = dbi_result_field_get_length_by_fieldname(row, fieldname);
		if (length > 0)
		{
			return dbi_result_get_binary(row, fieldname);
		}
	}

	return NULL;
}

/*
* 函数: dbi_result_get_datetime_value_by_fieldname
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		fieldname	字段名称
* 返回: time_t
*		- 0			失败
* 说明: 可以使用 gmtime 或者 localtime 转换可读格式
*/
time_t dbi_result_get_datetime_value_by_fieldname(
	dbi_results_t row, const char *fieldname)
{
	if (row && fieldname)
	{
		return dbi_result_get_datetime(row, fieldname);
	}

	return 0;
}

/*
* 函数: dbi_result_get_char_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: char
*		- 0		失败
* 说明: 
*/
char dbi_result_get_char_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_char_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_uchar_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: unsigned char
*		- 0		失败
* 说明: 
*/
unsigned char dbi_result_get_uchar_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_uchar_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_short_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: short
*		- 0			失败
* 说明: 
*/
short dbi_result_get_short_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx> 0)
	{
		return dbi_result_get_short_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_ushort_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: unsigned short
*		- 0			失败
* 说明: 
*/
unsigned short dbi_result_get_ushort_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_ushort_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_int_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: int
*		- 0		失败
* 说明: 
*/
int dbi_result_get_int_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_int_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_uint_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: unsigned int
*		- 0			失败
* 说明: 
*/
unsigned int dbi_result_get_uint_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_uint_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_long_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: int
*		- 0			失败
* 说明: 
*/
int dbi_result_get_long_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	return dbi_result_get_int_value_by_idx(row, idx);
}

/*
* 函数: dbi_result_get_ulong_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: unsigned int
*		- 0			失败
* 说明: 
*/
unsigned int dbi_result_get_ulong_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	return dbi_result_get_uint_value_by_idx(row, idx);
}

/*
* 函数: dbi_result_get_longlong_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: long long
*		- 0			失败
* 说明: 
*/
long long dbi_result_get_longlong_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_longlong_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_ulonglong_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: unsigned long long
*		- 0			失败
* 说明: 
*/
unsigned long long dbi_result_get_ulonglong_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_ulonglong_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_float_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: float
*		- 0			失败
* 说明: 
*/
float dbi_result_get_float_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_float_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_double_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: double
*		- 0			失败
* 说明: 
*/
double dbi_result_get_double_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_double_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_get_string_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: const char *
*		- NULL		失败
* 说明: 
*/
const char *dbi_result_get_string_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_string_idx(row, idx);
	}

	return NULL;
}

/*
* 函数: dbi_result_get_binary_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: const unsigned char *
*		- NULL		失败
* 说明: 
*/
const unsigned char *dbi_result_get_binary_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	size_t length = 0;
	if (row && idx > 0)
	{
		length = dbi_result_field_get_length_by_idx(row, idx);
		if (length > 0)
		{
			return dbi_result_get_binary_idx(row, idx);
		}
	}

	return NULL;
}

/*
* 函数: dbi_result_get_datetime_value_by_idx
* 功能: 获取在row中指定字段的值
* 参数: row			结果集合的行
*		idx			序号，从1开始
* 返回: time_t
*		- 0			失败
* 说明: 可以使用 gmtime 或者 localtime 转换可读格式
*/
time_t dbi_result_get_datetime_value_by_idx(
	dbi_results_t row, unsigned int idx)
{
	if (row && idx > 0)
	{
		return dbi_result_get_datetime_idx(row, idx);
	}

	return 0;
}

/*
* 函数: dbi_result_field_bind_char_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_char_value(
	dbi_results_t result, const char *fieldname, char value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_char(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_uchar_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_uchar_value(
	dbi_results_t result, const char *fieldname, unsigned char value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_uchar(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_short_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_short_value(
	dbi_results_t result, const char *fieldname, short value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_short(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_ushort_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_ushort_value(
	dbi_results_t result, const char *fieldname, unsigned short value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_ushort(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_int_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_int_value(
	dbi_results_t result, const char *fieldname, int value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_int(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_uint_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_uint_value(
	dbi_results_t result, const char *fieldname, unsigned int value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_uint(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_long_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_long_value(
	dbi_results_t result, const char *fieldname, long value)
{
	return dbi_result_field_bind_int_value(result, fieldname, value);
}

/*
* 函数: dbi_result_field_bind_ulong_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_ulong_value(
	dbi_results_t result, const char *fieldname, unsigned long value)
{
	return dbi_result_field_bind_uint_value(result, fieldname, value);
}

/*
* 函数: dbi_result_field_bind_longlong_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_longlong_value(
	dbi_results_t result, const char *fieldname, long long value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_longlong(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_ulonglong_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_ulonglong_value(
	dbi_results_t result, const char *fieldname, unsigned long long value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_ulonglong(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_float_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_float_value(
	dbi_results_t result, const char *fieldname, float value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_float(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_double_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合的行
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_double_value(
	dbi_results_t result, const char *fieldname, double value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_double(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_string_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_string_value(
	dbi_results_t result, const char *fieldname, const char *value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_string(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_binary_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_binary_value(
	dbi_results_t result, const char *fieldname, const unsigned char *value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_binary(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bind_datetime_value
* 功能: 在result集合中新增字段和值
* 参数: result			结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_datetime_value(
	dbi_results_t result, const char *fieldname, time_t value)
{
	if (result && fieldname)
	{
		return ! dbi_result_bind_datetime(result, fieldname, &value);
	}

	return false;
}

/*
* 函数: dbi_result_field_bindf
* 功能: 在result集合中批量新增字段和值
* 参数: result	结果集合
*		fmt 	格式化字符串，类似printf函数格式
*		... 	格式化参数列表
* 返回: unsigned int	绑定成功字段数量
*		- 0 			失败
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
unsigned int dbi_result_field_bindf(
	dbi_results_t result, const char *format, ...)
{
	unsigned int numtokens = 0;
	va_list ap;
	va_start(ap, format);
	numtokens = dbi_result_field_bindf2(result, format, ap);
	va_end(ap);
	
	return numtokens;
}

/*
* 函数: dbi_result_field_bindf2
* 功能: 在result集合中批量新增字段和值
* 参数: result	结果集合
*		fmt 	格式化字符串，类似printf函数格式
*		args 	格式化参数列表
* 返回: unsigned int	绑定成功字段数量
*		- 0 			失败
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
unsigned int dbi_result_field_bindf2(
	dbi_results_t result, const char *format, va_list args)
{
	char **tokens = NULL;
	char **fieldnames = NULL;
	unsigned int curidx = 0;
	unsigned int numtokens = 0;
	bool uflag = false;
	va_list ap;
	va_copy(ap, args);

	if (result == NULL)
	{
		return 0;
	}
	
	numtokens = bdi_parse_field_formatstr(format, &tokens, &fieldnames);
	if (numtokens == 0)
	{
		return 0;
	}

#define assert_return(ret, msg)	\
	do { \
		if (ret == false) \
		{ \
			LOG_TRACE(msg); \
		} \
	} while (0)

	while (curidx < numtokens)
	{
		uflag = strlen(tokens[curidx]) > 1 && tokens[curidx][0] == 'u';
		switch (tokens[curidx][strlen(tokens[curidx]) - 1])
		{
			//对于va_arg()可变参数类型需要向上提升
			//char short / uchar ushort -> int / uint
			//float -> double
			case 'c':
			{
				if (uflag)
				{
					assert_return(
						dbi_result_field_bind_uchar_value(
								result, fieldnames[curidx], 
								va_arg(ap, unsigned int)), 
						"dbi_result_field_bind_uchar_value error!\n");
				}
				else
				{
					assert_return(
						dbi_result_field_bind_char_value(
								result, fieldnames[curidx], 
								va_arg(ap, int)), 
						"dbi_result_field_bind_char_value error!\n");
				}
				break;
			}
			case 'h': //short
			{
				if (uflag)
				{
					assert_return(
						dbi_result_field_bind_ushort_value(
								result, fieldnames[curidx], 
								va_arg(ap, unsigned int)), 
						"dbi_result_field_bind_ushort_value error!\n");
				}
				else
				{
					assert_return(
						dbi_result_field_bind_short_value(
								result, fieldnames[curidx], 
								va_arg(ap, int)), 
						"dbi_result_field_bind_short_value error!\n");
				}
				break;
			}
			case 'l':
			case 'i':
			{
				if (uflag)
				{
					assert_return(
						dbi_result_field_bind_uint_value(
								result, fieldnames[curidx], 
								va_arg(ap, unsigned int)), 
						"dbi_result_field_bind_uint_value error!\n");
				}
				else
				{
					assert_return(
						dbi_result_field_bind_int_value(
								result, fieldnames[curidx], 
								va_arg(ap, int)), 
						"dbi_result_field_bind_int_value error!\n");
				}
				break;
			}
			case 'L': //long long
			{
				if (uflag)
				{
					assert_return(
						dbi_result_field_bind_ulonglong_value(
								result, fieldnames[curidx], 
								va_arg(ap, unsigned long long)), 
						"dbi_result_field_bind_ulonglong_value error!\n");
				}
				else
				{
					assert_return(
						dbi_result_field_bind_longlong_value(
								result, fieldnames[curidx], 
								va_arg(ap, long long)), 
						"dbi_result_field_bind_longlong_value error!\n");
				}
				break;
			}
			case 'f':
			{
				assert_return(
					dbi_result_field_bind_float_value(
							result, fieldnames[curidx], 
							va_arg(ap, double)), 
					"dbi_result_field_bind_float_value error!\n");
				break;
			}
			case 'd': //double
			{
				assert_return(
					dbi_result_field_bind_double_value(
							result, fieldnames[curidx], 
							va_arg(ap, double)), 
					"dbi_result_field_bind_double_value error!\n");
				break;
			}
			case 's': //string
			{
				assert_return(
					dbi_result_field_bind_string_value(
							result, fieldnames[curidx], 
							va_arg(ap, const char *)), 
					"dbi_result_field_bind_string_value error!\n");
				break;
			}
			case 'b': //binary
			{
				assert_return(
					dbi_result_field_bind_binary_value(
							result, fieldnames[curidx], 
							va_arg(ap, const unsigned char *)), 
					"dbi_result_field_bind_binary_value error!\n");
				break;
			}
			case 't': //datetime 实际是time_t
			{
				assert_return(
					dbi_result_field_bind_datetime_value(
							result, fieldnames[curidx], 
							va_arg(ap, time_t)), 
					"dbi_result_field_bind_datetime_value error!\n");
			}
			break;
		}
		
		curidx ++;
	}
	
	va_end(ap);

	dbi_free_string_list(tokens, numtokens);
	dbi_free_string_list(fieldnames, numtokens);
	
	return numtokens;
#undef assert_return
}

/*
* 函数: dbi_result_field_get_values
* 功能: 在row中批量获取字段的值
* 参数: result	结果集合
*		fmt 	格式化字符串，类似printf函数格式
*		... 	格式化参数列表，用于保存获取到的值
* 返回: unsigned int	获取成功字段数量
*		- 0 			失败
* 说明: fmt 格式: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt字符串中必须是[字段名.格式化标识]，多个字段之间用空格隔开
*		... 为可变参数，每个参数传参必须加上取地址符号 &
*		举例: dbi_result_field_get_values(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
unsigned int dbi_result_field_get_values(
	dbi_results_t row, const char *format, ...)
{
	unsigned int numtokens = 0;
	va_list ap;
	va_start(ap, format);
	numtokens = dbi_result_field_get_values2(row, format, ap);
	va_end(ap);

	return numtokens;
}

/*
* 函数: dbi_result_field_get_values2
* 功能: 在row中批量获取字段的值
* 参数: result	结果集合
*		fmt 	格式化字符串，类似printf函数格式
*		args 	格式化参数列表，用于保存获取到的值
* 返回: unsigned int	获取成功字段数量
*		- 0 			失败
* 说明: fmt 格式: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt字符串中必须是[字段名.格式化标识]，多个字段之间用空格隔开
*		... 为可变参数，每个参数传参必须加上取地址符号 &
*		举例: dbi_result_field_get_values(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
unsigned int dbi_result_field_get_values2(
	dbi_results_t row, const char *format, va_list args)
{
	char **tokens = NULL;
	char **fieldnames = NULL;
	unsigned int curidx = 0;
	unsigned int numtokens = 0;
	bool uflag = false;
	va_list ap;

	if (row == NULL)
	{
		return 0;
	}

	numtokens = bdi_parse_field_formatstr(format, &tokens, &fieldnames);
	if (numtokens == 0)
	{
		return 0;
	}

#define assert_return(f, format, args...) \
	do { \
		if ((f) == 0) \
		{ \
			LOG_TRACE(format, args); \
		} \
	} while (0)
	
	va_copy(ap, args);
	while (curidx < numtokens)
	{
		uflag = strlen(tokens[curidx]) > 1 && tokens[curidx][0] == 'u';
		switch (tokens[curidx][strlen(tokens[curidx]) - 1])
		{
			case 'c':
			{
				if (uflag)
				{
					assert_return(*va_arg(ap, unsigned char *) = 
							dbi_result_get_uchar_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get uchar value error!\n", 
								fieldnames[curidx]);
				}
				else
				{
					assert_return(*va_arg(ap, char *) = 
							dbi_result_get_char_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get char value error!\n", 
								fieldnames[curidx]);
				}
				break;
			}
			case 'h': //short
			{
				if (uflag)
				{
					assert_return(*va_arg(ap, unsigned short *) = 
						dbi_result_get_ushort_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get ushort value error!\n", 
								fieldnames[curidx]);
				}
				else
				{
					assert_return(*va_arg(ap, short *) = 
						dbi_result_get_short_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get short value error!\n", 
								fieldnames[curidx]);
				}
				break;
			}
			case 'l': //long
			case 'i': //int
			{
				if (uflag)
				{
					assert_return(*va_arg(ap, unsigned int *) = 
						dbi_result_get_uint_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get ulong/uint value error!\n", 
								fieldnames[curidx]);
				}
				else
				{
					assert_return(*va_arg(ap, int *) = 
						dbi_result_get_int_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get ulong/uint value error!\n", 
								fieldnames[curidx]);
				}
				break;
			}
			case 'L': //long long
			{
				if (uflag)
				{
					assert_return(*va_arg(ap, unsigned long long *) = 
						dbi_result_get_ulonglong_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get ulonglong value error!\n", 
								fieldnames[curidx]);
				}
				else
				{
					assert_return(*va_arg(ap, long long *) = 
						dbi_result_get_longlong_value_by_fieldname(
								row, fieldnames[curidx]), 
							"the field '%s' get longlong value error!\n", 
								fieldnames[curidx]);
				}
				break;
			}
			case 'f':
			{
				assert_return(*va_arg(ap, float *) = 
					dbi_result_get_float_value_by_fieldname(
							row, fieldnames[curidx]), 
						"the field '%s' get float value error!\n", 
							fieldnames[curidx]);
				break;
			}
			case 'd': //double
			{
				assert_return(*va_arg(ap, double *) = 
					dbi_result_get_double_value_by_fieldname(
							row, fieldnames[curidx]), 
						"the field '%s' get double value error!\n", 
							fieldnames[curidx]);
				break;
			}
			case 's': //string
			{
				assert_return(*va_arg(ap, const char **) = 
					dbi_result_get_string_value_by_fieldname(
							row, fieldnames[curidx]), 
						"the field '%s' get string value error!\n", 
							fieldnames[curidx]);
				break;
			}
			case 'b': //unsigned char *
			{
				assert_return(*va_arg(ap, const unsigned char **) = 
					dbi_result_get_binary_value_by_fieldname(
							row, fieldnames[curidx]), 
						"the field '%s' get binary value error!\n", 
							fieldnames[curidx]);
				break;
			}
			case 't': //time_t
			{
				assert_return(*va_arg(ap, time_t *) = 
					dbi_result_get_datetime_value_by_fieldname(
							row, fieldnames[curidx]), 
						"the field '%s' get datetime value error!\n", 
							fieldnames[curidx]);
				break;
			}
		}

		curidx ++;
	}

	va_end(ap);

	dbi_free_string_list(tokens, numtokens);
	dbi_free_string_list(fieldnames, numtokens);

	return numtokens;
#undef assert_return
}


