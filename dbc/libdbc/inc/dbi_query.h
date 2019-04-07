#ifndef __DBI_QUERY_H__
#define __DBI_QUERY_H__

#include "dbi_object.h"

/*
* ����: dbi_query
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
*		sql		sql����ַ���
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: 
*/
dbi_results_t dbi_query(dbi_object_t obj, const char *sql);

/*
* ����: dbi_query_by_statement_buf
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: sql�����Դ��obj��Աstatement
*/
dbi_results_t dbi_query_by_statement_buf(dbi_object_t obj);

/*
* ����: dbi_queryf
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
*		fmt		��ʽ���ַ���������printf
*		...		��ʽ�������б�
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: fmt��... ��ͬ����һ��sql����ַ���
*/
dbi_results_t dbi_queryf(dbi_object_t obj, const char *fmt, ...);

/*
* ����: dbi_queryf2
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
*		fmt		��ʽ���ַ���������printf
*		args	��ʽ�������б�
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: fmt��... ��ͬ����һ��sql����ַ���
*		�������ڶ�������
*/
dbi_results_t dbi_queryf2(dbi_object_t obj, const char *sql_fmt, va_list args);

/*
* ����: dbi_query_db_list
* ����: ��ѯ���ݿ��б�
* ����: obj		dbi����
*		pattern	SQL������ʽ��Ϊ�����ѯ���п���
* ����: dbi_results_t	�������
*		- NULL ��ѯʧ��
* ˵��: 
*/
dbi_results_t dbi_query_db_list(dbi_object_t obj, const char *pattern);

/*
* ����: dbi_query_table_list
* ����: ��ѯ���ݱ��б�
* ����: obj		dbi����
*		db		���ݿ�
*		pattern	SQL������ʽ��Ϊ�����ѯ���п���
* ����: dbi_results_t	�������
*		- NULL ��ѯʧ��
* ˵��: 
*/
dbi_results_t dbi_query_table_list(dbi_object_t obj, 
	const char *db, const char *pattern);

/*
* ����: dbi_switches_db
* ����: �л����ݿ�
* ����: obj		dbi����
*		db		���ݿ�
* ����: bool
*		- false ʧ��
* ˵��: 
*/
bool dbi_switches_db(dbi_object_t obj, const char *db);

#endif

