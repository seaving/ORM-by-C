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
* ����: dbi_result_get_currow_idx
* ����: ��ȡ��ǰ��������еĵ�ǰ��
* ����: result		�������
* ����: unsigned long long	����
*		- 0 ��ѯʧ��
* ˵��: ������������Ǵ�1��ʼ��
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
* ����: dbi_result_get_rows_count
* ����: ��ȡ��ǰ���������������
* ����: result		�������
* ����: unsigned long long	����
* ˵��: 
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
* ����: dbi_result_row_seek
* ����: �������ƫ��
* ����: result		�������
*		offset		ƫ����
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: ƫ�ƻ�׼�Ǵӵ�ǰλ�ý���offsetƫ��
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
* ����: dbi_result_row_seek_to_first
* ����: �������ƫ�Ƶ���һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
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
* ����: dbi_result_row_seek_to_last
* ����: �������ƫ�Ƶ����һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
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
* ����: dbi_result_row_seek_to_prev
* ����: �������ƫ�Ƶ�ǰһ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
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
* ����: dbi_result_row_seek_to_next
* ����: �������ƫ�Ƶ���һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
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
* ����: dbi_result_row_add
* ����: ��result�������������һ��
* ����: result	�������
*		fmt 	��ʽ���ַ���������printf������ʽ
*		... 	��ʽ�������б�
* ����: bool
*		- false ʧ��
* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
*		����: dbi_result_row_add(row, "name.%s sex.%s age.%d", name, sex, age)
*	--- ��ʽ�ַ�:
*		%c / %uc: char / unsigned char
*		%h / %uh: short / unsigned short
*		%l / %ul: int / unsigned int(long��intһ��)
*		%i / %ui: int / unsigned int(long��intһ��)
*		%L / %uL: long long / unsigned long long
*		%f: float
*		%d: double
*		%s: string
*		%b: unsigned char * �������ַ���
*		%t: time_t ��ʾ���ں�/��ʱ���ʱ��ֵ
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

