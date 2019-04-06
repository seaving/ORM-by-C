#ifndef __DBI_RESULT_ROW_H__
#define __DBI_RESULT_ROW_H__

#include "dbi_object.h"

/*
* ����: dbi_result_get_currow_idx
* ����: ��ȡ��ǰ��������еĵ�ǰ��
* ����: result		�������
* ����: unsigned long long	����
*		- 0 ��ѯʧ��
* ˵��: ������������Ǵ�1��ʼ��
*/
unsigned long long dbi_result_get_currow_idx(dbi_results_t result);

/*
* ����: dbi_result_get_rows_count
* ����: ��ȡ��ǰ���������������
* ����: result		�������
* ����: unsigned long long	����
* ˵��: 
*/
unsigned long long dbi_result_get_rows_count(dbi_results_t result);

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
bool dbi_result_row_seek(dbi_results_t result, unsigned long long offset);

/*
* ����: dbi_result_row_seek_to_first
* ����: �������ƫ�Ƶ���һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
*/
bool dbi_result_row_seek_to_first(dbi_results_t result);

/*
* ����: dbi_result_row_seek_to_last
* ����: �������ƫ�Ƶ����һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
*/
bool dbi_result_row_seek_to_last(dbi_results_t result);

/*
* ����: dbi_result_row_seek_to_prev
* ����: �������ƫ�Ƶ�ǰһ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
*/
bool dbi_result_row_seek_to_prev(dbi_results_t result);

/*
* ����: dbi_result_row_seek_to_next
* ����: �������ƫ�Ƶ���һ��
* ����: result		�������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: 
*/
bool dbi_result_row_seek_to_next(dbi_results_t result);

/*
* ����: dbi_result_row_foreach
* ����: �����������
* ����: result		dbi_results_t �������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: resultָ��ǰ�У�������ѭ������ͨ��api��ȡ��ǰ�и����ֶ���Ϣ
*/
#define dbi_result_row_foreach(result) \
	while (dbi_result_row_seek_to_next(result))

/*
* ����: dbi_result_row_foreach_from
* ����: ��offsetλ�ÿ�ʼ�����������
* ����: bool_ret	bool���ͣ�ѭ�����ڲ�����������ʹ����ֻ�趨��ret�������д���
*		result		dbi_results_t �������
*		ull_offset	unsigned long long ƫ����
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: resultָ��ǰ�У�������ѭ������ͨ��api��ȡ��ǰ�и����ֶ���Ϣ
*
*/
#define dbi_result_row_foreach_from(bool_ret, result, ull_offset) \
	for (bool_ret = dbi_result_row_seek(result, ull_offset); \
			bool_ret == true || dbi_result_row_seek_to_next(result); \
			bool_ret = false)

/*
* ����: dbi_result_row_foreach_limit
* ����: ��offsetλ�ÿ�ʼ����������ϣ���������Ϊlimit
* ����: bool_ret 	bool ѭ�����ڲ�����������ʹ����ֻ�趨��ret�������д���
*		uint_n		unsigned int ѭ�����ڲ�����������ʹ����ֻ�趨��n�������д���
*		result		dbi_results_t �������
*		ull_offset	unsigned long long ƫ����
*		uint_limit	unsigned int	 ����������
* ����: bool
*		- false: ʧ��
*		- true: �ɹ�
* ˵��: resultָ��ǰ�У�������ѭ������ͨ��api��ȡ��ǰ�и����ֶ���Ϣ
*
*/
#define dbi_result_row_foreach_limit(bool_ret, uint_n, result, ull_offset, uint_limit) \
		for (uint_n = 0, bool_ret = dbi_result_row_seek(result, ull_offset); \
				bool_ret == true || (uint_n < uint_limit \
					&& dbi_result_row_seek_to_next(result)); \
				uint_n ++, bool_ret = false)

		
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
	dbi_results_t result, const char *fmt, ...);

#endif

