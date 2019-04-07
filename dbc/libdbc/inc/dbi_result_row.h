#ifndef __DBI_RESULT_ROW_H__
#define __DBI_RESULT_ROW_H__

#include "dbi_object.h"

/*
* 函数: dbi_result_get_currow_idx
* 功能: 获取当前结果集合中的当前行
* 参数: result		结果集合
* 返回: unsigned long long	行数
*		- 0 查询失败
* 说明: 结果集合行数是从1开始的
*/
unsigned long long dbi_result_get_currow_idx(dbi_results_t result);

/*
* 函数: dbi_result_get_rows_count
* 功能: 获取当前结果集合中总行数
* 参数: result		结果集合
* 返回: unsigned long long	行数
* 说明: 
*/
unsigned long long dbi_result_get_rows_count(dbi_results_t result);

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
bool dbi_result_row_seek(dbi_results_t result, unsigned long long offset);

/*
* 函数: dbi_result_row_seek_to_first
* 功能: 结果集合偏移到第一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_first(dbi_results_t result);

/*
* 函数: dbi_result_row_seek_to_last
* 功能: 结果集合偏移到最后一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_last(dbi_results_t result);

/*
* 函数: dbi_result_row_seek_to_prev
* 功能: 结果集合偏移到前一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_prev(dbi_results_t result);

/*
* 函数: dbi_result_row_seek_to_next
* 功能: 结果集合偏移到下一行
* 参数: result		结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: 
*/
bool dbi_result_row_seek_to_next(dbi_results_t result);

/*
* 函数: dbi_result_row_foreach
* 功能: 遍历结果集合
* 参数: result		dbi_results_t 结果集合
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: result指向当前行，可以在循环体中通过api获取当前行各个字段信息
*/
#define dbi_result_row_foreach(result) \
	while (dbi_result_row_seek_to_next(result))

/*
* 函数: dbi_result_row_foreach_from
* 功能: 从offset位置开始遍历结果集合
* 参数: bool_ret	bool类型，循环中内部辅助变量，使用中只需定义ret变量进行传参
*		result		dbi_results_t 结果集合
*		ull_offset	unsigned long long 偏移量
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: result指向当前行，可以在循环体中通过api获取当前行各个字段信息
*
*/
#define dbi_result_row_foreach_from(bool_ret, result, ull_offset) \
	for (bool_ret = dbi_result_row_seek(result, ull_offset); \
			bool_ret == true || dbi_result_row_seek_to_next(result); \
			bool_ret = false)

/*
* 函数: dbi_result_row_foreach_limit
* 功能: 从offset位置开始遍历结果集合，遍历步长为limit
* 参数: bool_ret 	bool 循环中内部辅助变量，使用中只需定义ret变量进行传参
*		uint_n		unsigned int 循环中内部辅助变量，使用中只需定义n变量进行传参
*		result		dbi_results_t 结果集合
*		ull_offset	unsigned long long 偏移量
*		uint_limit	unsigned int	 遍历的数量
* 返回: bool
*		- false: 失败
*		- true: 成功
* 说明: result指向当前行，可以在循环体中通过api获取当前行各个字段信息
*
*/
#define dbi_result_row_foreach_limit(bool_ret, uint_n, result, ull_offset, uint_limit) \
		for (uint_n = 0, bool_ret = dbi_result_row_seek(result, ull_offset); \
				bool_ret == true || (uint_n < uint_limit \
					&& dbi_result_row_seek_to_next(result)); \
				uint_n ++, bool_ret = false)

		
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
	dbi_results_t result, const char *fmt, ...);

#endif

