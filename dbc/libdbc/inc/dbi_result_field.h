#ifndef __DBI_RESULT_FIELD_H__
#define __DBI_RESULT_FIELD_H__

#include "dbi_object.h"

/*
* ����: dbi_result_field_get_length_by_fieldname
* ����: ͨ��fieldname��ȡ���ֶ����ݵĳ���
* ����: row		������ϵ���
* ����: size_t
* ˵��: �����ַ������߶������ַ���������ֶ����͵����ݳ��ȷ���0
*		���� Int�͵��ֶ����ݳ����򷵻�0
*/
size_t dbi_result_field_get_length_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_field_get_length_by_idx
* ����: ͨ�����кŻ�ȡ���ֶεĳ���
* ����: row		������ϵ���
*		idx		���еĵڼ��У�����Ǵ�1��ʼ��
* ����: size_t
* ˵��: ���к��Ǵ�1��ʼ��
*		�����ַ������߶������ַ���������ֶ����͵����ݳ��ȷ���0
*		���� Int�͵��ֶ����ݳ����򷵻�0
*/
size_t dbi_result_field_get_length_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_field_get_idx
* ����: ��ѯ�ֶ���row�е����
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned int
*		- > 0	���ֶε����
*		- = 0	����
* ˵��: ���к��Ǵ�1��ʼ��
*/
unsigned int dbi_result_field_get_idx(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_field_get_name
* ����: ��row�в�ѯָ����ŵ��ֶ�����
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: const char *
*		- NULL		��ѯʧ��
* ˵��: ���к��Ǵ�1��ʼ��
*/
const char *dbi_result_field_get_name(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_field_get_count
* ����: ��row��ͳ���ֶ�����
* ����: row			������ϵ���
* ����: unsigned int
*		- 0			ʧ��
* ˵��: ���к��Ǵ�1��ʼ��
*/
unsigned int dbi_result_field_get_count(dbi_results_t row);

/*
* ����: dbi_result_field_get_type_by_fieldname
* ����: ��row��ָ���ֶε�����
* ����: row			������ϵ���
*		fieldname	�ֶ���
* ����: unsigned short
*		- 0			ʧ��
* ˵��: 
*/
unsigned short dbi_result_field_get_type_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_field_get_type_by_idx
* ����: ��row��ָ���ֶε�����
* ����: row			������ϵ���
*		idx			��ţ���Ҫ��1��ʼ
* ����: unsigned short
*		- 0			ʧ��
* ˵��: 
*/
unsigned short dbi_result_field_get_type_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_field_is_null_value_by_fieldname
* ����: ��row��ָ���ֶε�ֵ�Ƿ�Ϊ��
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: bool
*		- false		ʧ��
*		- true		Ϊ��
* ˵��: 
*/
bool dbi_result_field_is_null_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_field_is_null_value_by_idx
* ����: ��row��ָ���ֶε�ֵ�Ƿ�Ϊ��
* ����: row			������ϵ���
*		idx			��ţ���Ҫ��1��ʼ
* ����: bool
*		- false		ʧ��
*		- true		Ϊ��
* ˵��: 
*/
bool dbi_result_field_is_null_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_char_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: char
*		- 0		ʧ��
* ˵��: 
*/
char dbi_result_get_char_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_uchar_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned char
*		- 0		ʧ��
* ˵��: 
*/
unsigned char dbi_result_get_uchar_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_short_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: short
*		- 0			ʧ��
* ˵��: 
*/
short dbi_result_get_short_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_ushort_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned short
*		- 0			ʧ��
* ˵��: 
*/
unsigned short dbi_result_get_ushort_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_int_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: int
*		- 0		ʧ��
* ˵��: 
*/
int dbi_result_get_int_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_uint_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned int
*		- 0			ʧ��
* ˵��: 
*/
unsigned int dbi_result_get_uint_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_long_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: int
*		- 0			ʧ��
* ˵��: 
*/
int dbi_result_get_long_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_ulong_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned int
*		- 0			ʧ��
* ˵��: 
*/
unsigned int dbi_result_get_ulong_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_longlong_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: long long
*		- 0			ʧ��
* ˵��: 
*/
long long dbi_result_get_longlong_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_ulonglong_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: unsigned long long
*		- 0			ʧ��
* ˵��: 
*/
unsigned long long dbi_result_get_ulonglong_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_float_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: float
*		- 0			ʧ��
* ˵��: 
*/
float dbi_result_get_float_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_double_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: double
*		- 0			ʧ��
* ˵��: 
*/
double dbi_result_get_double_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_string_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: const char *
*		- NULL		ʧ��
* ˵��: 
*/
const char *dbi_result_get_string_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_binary_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: const unsigned char *
*		- NULL		ʧ��
* ˵��: 
*/
const unsigned char *dbi_result_get_binary_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_datetime_value_by_fieldname
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		fieldname	�ֶ�����
* ����: time_t
*		- 0			ʧ��
* ˵��: ����ʹ�� gmtime ���� localtime ת���ɶ���ʽ
*/
time_t dbi_result_get_datetime_value_by_fieldname(
	dbi_results_t row, const char *fieldname);

/*
* ����: dbi_result_get_char_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: char
*		- 0		ʧ��
* ˵��: 
*/
char dbi_result_get_char_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_uchar_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: unsigned char
*		- 0		ʧ��
* ˵��: 
*/
unsigned char dbi_result_get_uchar_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_short_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: short
*		- 0			ʧ��
* ˵��: 
*/
short dbi_result_get_short_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_ushort_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: unsigned short
*		- 0			ʧ��
* ˵��: 
*/
unsigned short dbi_result_get_ushort_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_int_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: int
*		- 0		ʧ��
* ˵��: 
*/
int dbi_result_get_int_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_uint_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: unsigned int
*		- 0			ʧ��
* ˵��: 
*/
unsigned int dbi_result_get_uint_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_long_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: int
*		- 0			ʧ��
* ˵��: 
*/
int dbi_result_get_long_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_ulong_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: unsigned int
*		- 0			ʧ��
* ˵��: 
*/
unsigned int dbi_result_get_ulong_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_longlong_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: long long
*		- 0			ʧ��
* ˵��: 
*/
long long dbi_result_get_longlong_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_ulonglong_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: unsigned long long
*		- 0			ʧ��
* ˵��: 
*/
unsigned long long dbi_result_get_ulonglong_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_float_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: float
*		- 0			ʧ��
* ˵��: 
*/
float dbi_result_get_float_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_double_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: double
*		- 0			ʧ��
* ˵��: 
*/
double dbi_result_get_double_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_string_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: const char *
*		- NULL		ʧ��
* ˵��: 
*/
const char *dbi_result_get_string_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_binary_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: const unsigned char *
*		- NULL		ʧ��
* ˵��: 
*/
const unsigned char *dbi_result_get_binary_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_get_datetime_value_by_idx
* ����: ��ȡ��row��ָ���ֶε�ֵ
* ����: row			������ϵ���
*		idx			��ţ���1��ʼ
* ����: time_t
*		- 0			ʧ��
* ˵��: ����ʹ�� gmtime ���� localtime ת���ɶ���ʽ
*/
time_t dbi_result_get_datetime_value_by_idx(
	dbi_results_t row, unsigned int idx);

/*
* ����: dbi_result_field_bind_char_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_char_value(
	dbi_results_t result, const char *fieldname, char value);

/*
* ����: dbi_result_field_bind_uchar_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_uchar_value(
	dbi_results_t result, const char *fieldname, unsigned char value);

/*
* ����: dbi_result_field_bind_short_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_short_value(
	dbi_results_t result, const char *fieldname, short value);

/*
* ����: dbi_result_field_bind_ushort_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_ushort_value(
	dbi_results_t result, const char *fieldname, unsigned short value);

/*
* ����: dbi_result_field_bind_int_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_int_value(
	dbi_results_t result, const char *fieldname, int value);

/*
* ����: dbi_result_field_bind_uint_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_uint_value(
	dbi_results_t result, const char *fieldname, unsigned int value);

/*
* ����: dbi_result_field_bind_long_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_long_value(
	dbi_results_t result, const char *fieldname, long value);

/*
* ����: dbi_result_field_bind_ulong_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_ulong_value(
	dbi_results_t result, const char *fieldname, unsigned long value);

/*
* ����: dbi_result_field_bind_longlong_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_longlong_value(
	dbi_results_t result, const char *fieldname, long long value);

/*
* ����: dbi_result_field_bind_ulonglong_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_ulonglong_value(
	dbi_results_t result, const char *fieldname, unsigned long long value);

/*
* ����: dbi_result_field_bind_float_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_float_value(
	dbi_results_t result, const char *fieldname, float value);

/*
* ����: dbi_result_field_bind_double_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_double_value(
	dbi_results_t result, const char *fieldname, double value);

/*
* ����: dbi_result_field_bind_string_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_string_value(
	dbi_results_t result, const char *fieldname, const char *value);

/*
* ����: dbi_result_field_bind_binary_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_binary_value(
	dbi_results_t result, const char *fieldname, const unsigned char *value);

/*
* ����: dbi_result_field_bind_datetime_value
* ����: ��result�����������ֶκ�ֵ
* ����: result		�������
*		fieldname 	�ֶ���
*		value		�󶨵�ֵ
* ����: bool
*		- false		ʧ��
* ˵��: 
*/
bool dbi_result_field_bind_datetime_value(
	dbi_results_t result, const char *fieldname, time_t value);

/*
* ����: dbi_result_field_bindf
* ����: ��result���������������ֶκ�ֵ
* ����: result	�������
*		fmt 	��ʽ���ַ���������printf������ʽ
*		... 	��ʽ�������б�
* ����: unsigned int	�󶨳ɹ��ֶ�����
*		- 0 			ʧ��
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
unsigned int dbi_result_field_bindf(
	dbi_results_t result, const char *format, ...);

/*
* ����: dbi_result_field_bindf2
* ����: ��result���������������ֶκ�ֵ
* ����: result	�������
*		fmt 	��ʽ���ַ���������printf������ʽ
*		args 	��ʽ�������б�
* ����: unsigned int	�󶨳ɹ��ֶ�����
*		- 0 			ʧ��
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
unsigned int dbi_result_field_bindf2(
	dbi_results_t result, const char *format, va_list args);

/*
* ����: dbi_result_field_get_values
* ����: ��row��������ȡ�ֶε�ֵ
* ����: result	�������
*		fmt 	��ʽ���ַ���������printf������ʽ
*		... 	��ʽ�������б����ڱ����ȡ����ֵ
* ����: unsigned int	��ȡ�ɹ��ֶ�����
*		- 0 			ʧ��
* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
*		... Ϊ�ɱ������ÿ���������α������ȡ��ַ���� &
*		����: dbi_result_field_get_values(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
unsigned int dbi_result_field_get_values(
	dbi_results_t row, const char *format, ...);

/*
* ����: dbi_result_field_get_values2
* ����: ��row��������ȡ�ֶε�ֵ
* ����: result	�������
*		fmt 	��ʽ���ַ���������printf������ʽ
*		args 	��ʽ�������б����ڱ����ȡ����ֵ
* ����: unsigned int	��ȡ�ɹ��ֶ�����
*		- 0 			ʧ��
* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
*		... Ϊ�ɱ������ÿ���������α������ȡ��ַ���� &
*		����: dbi_result_field_get_values(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
unsigned int dbi_result_field_get_values2(
	dbi_results_t row, const char *format, va_list args);

#endif

