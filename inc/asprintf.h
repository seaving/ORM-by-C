#ifndef __ASPRINTF_H__
#define __ASPRINTF_H__

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
int vasprintf(char **result, const char *format, va_list args);

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
int asprintf(char **result, const char *format, ...);


#endif


