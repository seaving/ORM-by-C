#ifndef __ASPRINTF_H__
#define __ASPRINTF_H__

#include "sys_inc.h"

/*
* 函数: vasprintf
* 功能: 格式化可变参数字符串
* 参数: result	保存格式化的字符串
*		format	带格式化字符串，与printf一样
*		args	参数列表
* 返回: int		字符串长度
*		- 0		失败
* 说明: result 使用完要释放
*		该函数可用于二级可变参数传参
*/
int vasprintf(char **result, const char *format, va_list args);

/*
* 函数: asprintf
* 功能: 连接mysql数据库之前需要填充一些参数
* 参数: result	保存格式化的字符串
*		format	带格式化字符串，与printf一样
*		...		参数列表
* 返回: int		字符串长度
*		- 0		失败
* 说明: result 使用完要释放
*		该函数用于一级可变参数传参
*/
int asprintf(char **result, const char *format, ...);

#endif


