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
int vasprintf(char **result, const char *format, va_list args)
{
    const char *p = format;
    int total_width = strlen(format) + 1;
    va_list ap;

    va_copy(ap, args);

    while (*p != '\0')
    {
        if (*p ++ == '%')
		{
	        while (strchr ("-+ #0", *p))
	        {
	        	++ p;
	        }

	        if (*p == '*')
	        {
				++ p;
				total_width += abs(va_arg(ap, int));
	        }
	        else
	        {
	        	total_width += (unsigned long) strtol(p, (char**) &p, 10);
	        }
	        
	        if (*p == '.')
	        {
				++ p;

				if (*p == '*')
				{
					++ p;
					total_width += abs(va_arg(ap, int));
				}
				else
				{
					total_width += (unsigned long) strtol(p, (char**) &p, 10);
				}
	        }

	        while (strchr ("hlL", *p))
	        {
	        	++ p;
	        }
	        
	        total_width += 30;

	        switch (*p)
	        {
				case 'd':
				case 'i':
				case 'o':
				case 'u':
				case 'x':
				case 'X':
				case 'c':
					(void) va_arg(ap, int);
				    break;
				case 'f':
				case 'e':
				case 'E':
				case 'g':
				case 'G':
				    (void) va_arg(ap, double);
				    total_width += 307;
				    break;
				case 's':
				    total_width += strlen(va_arg(ap, char*));
				    break;
				case 'p':
				case 'n':
					(void) va_arg(ap, char*);
					break;
	        }
		}
    }

    *result = malloc(total_width);
    va_end(ap);
    if (*result != NULL)
    {
		return vsprintf(*result, format, args);
    }
    else
    {
		return 0;
    }
}

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
int asprintf(char **result, const char *format, ...)
{
	va_list va;
	int ret;

	va_start(va, format);
	ret = vasprintf(result, format, va);
	va_end(va);

	return ret;
}


