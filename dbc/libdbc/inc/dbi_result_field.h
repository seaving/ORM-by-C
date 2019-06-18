#ifndef __DBI_RESULT_FIELD_H__
#define __DBI_RESULT_FIELD_H__

#include "dbi_object.h"


/*
* 函数: bdi_result_parse_field_formatstr
* 功能: 解析format字符串
* 参数: 
* 返回: 
* 说明: 
*/
unsigned int bdi_parse_field_formatstr(
	const char *format, char ***tokens_dest, char ***fieldnames_dest);

/*
* 函数: _dbi_free_string_list
* 功能: 
* 参数: 
* 返回: 
* 说明: 
*/
void dbi_free_string_list(char **ptrs, int total);

/*
* 函数: dbi_result_field_get_length_by_fieldname
* 功能: 通过fieldname获取该字段内容的长度
* 参数: row		结果集合的行
* 返回: size_t
* 说明: 对于字符串或者二进制字符串以外的字段类型的内容长度返回0
*		例如 Int型的字段内容长度则返回0
*/
size_t dbi_result_field_get_length_by_fieldname(
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, unsigned int idx);

/*
* 函数: dbi_result_field_get_count
* 功能: 在row中统计字段数量
* 参数: row			结果集合的行
* 返回: unsigned int
*		- 0			失败
* 说明: 序列号是从1开始的
*/
unsigned int dbi_result_field_get_count(dbi_results_t row);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, const char *fieldname);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t row, unsigned int idx);

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
	dbi_results_t result, const char *fieldname, char value);

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
	dbi_results_t result, const char *fieldname, unsigned char value);

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
	dbi_results_t result, const char *fieldname, short value);

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
	dbi_results_t result, const char *fieldname, unsigned short value);

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
	dbi_results_t result, const char *fieldname, int value);

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
	dbi_results_t result, const char *fieldname, unsigned int value);

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
	dbi_results_t result, const char *fieldname, long value);

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
	dbi_results_t result, const char *fieldname, unsigned long value);

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
	dbi_results_t result, const char *fieldname, long long value);

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
	dbi_results_t result, const char *fieldname, unsigned long long value);

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
	dbi_results_t result, const char *fieldname, float value);

/*
* 函数: dbi_result_field_bind_double_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_double_value(
	dbi_results_t result, const char *fieldname, double value);

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
	dbi_results_t result, const char *fieldname, const char *value);

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
	dbi_results_t result, const char *fieldname, const unsigned char *value);

/*
* 函数: dbi_result_field_bind_datetime_value
* 功能: 在result集合中新增字段和值
* 参数: result		结果集合
*		fieldname 	字段名
*		value		绑定的值
* 返回: bool
*		- false		失败
* 说明: 
*/
bool dbi_result_field_bind_datetime_value(
	dbi_results_t result, const char *fieldname, time_t value);

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
	dbi_results_t result, const char *format, ...);

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
	dbi_results_t result, const char *format, va_list args);

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
	dbi_results_t row, const char *format, ...);

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
	dbi_results_t row, const char *format, va_list args);

#endif

