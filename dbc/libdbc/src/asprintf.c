#include "sys_inc.h"

/*
* ����: vasprintf
* ����: ��ʽ���ɱ�����ַ���
* ����: result	�����ʽ�����ַ���
*		format	����ʽ���ַ�������printfһ��
*		args	�����б�
* ����: int		�ַ�������
*		- 0		ʧ��
* ˵��: result ʹ����Ҫ�ͷ�
*		�ú��������ڶ����ɱ��������
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
* ����: asprintf
* ����: ����mysql���ݿ�֮ǰ��Ҫ���һЩ����
* ����: result	�����ʽ�����ַ���
*		format	����ʽ���ַ�������printfһ��
*		...		�����б�
* ����: int		�ַ�������
*		- 0		ʧ��
* ˵��: result ʹ����Ҫ�ͷ�
*		�ú�������һ���ɱ��������
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


