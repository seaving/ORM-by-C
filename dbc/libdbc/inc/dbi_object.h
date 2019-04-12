/********************************************************************************
* @File name: dbi_object.h
* @Author: caixiwen
* @Date: 2019-4-1
* @Description: The function interface
*

libdbi ��Ҫ�ȱ��밲װlibdbi��ܣ��ٰ�װlibdbi driver
�ڰ�װdriverʱ����Ҫ��װ���ݿ��lib�ļ�
����:
	sqlite3 driver��װ:
		�Ȱ�װlibsqlite3���ӹ����������µ�sqlite�����밲װ
		��ε�libdbi driverԴ����ִ�� ./configure --with-sqlite3���а�װdriver
		ע��: sqlite3�汾����ѡ���°汾���ϰ汾���������sqlite���ȱ�ٺ���������
		��libdbi��ƥ�䣬�����޷�����driver
********************************************************************************/

#ifndef __DBI_OBJECT_H__
#define __DBI_OBJECT_H__

#include "sys_inc.h"

#define DBI_STATEMENT_BUF_SIZE	8 * 1024

typedef struct __dbi_instance__
{
	dbi_conn conn;
	dbi_result result;
	dbi_inst instance;

	char statement[DBI_STATEMENT_BUF_SIZE];

	char driverdir[256];
	char sql_name[64];
	char drivername[64];
	char hostname[256];
	char username[64];
	char password[64];
	char dbdir[256];
	char dbname[64];
	char encoding[20];
	char version[64];
	int query_log;
} dbi_instance_t;

typedef intptr_t dbi_object_t;
typedef dbi_result dbi_results_t;

#define DBI_OBJECT_NULL		(0)

/*
* ����: dbi_object_new
* ����: ��������ʵ��
* ����: ��
* ����: dbi����
*		- 0		ʧ��
* ˵��: 
*/
dbi_object_t dbi_object_new();

/*
* ����: dbi_object_delete
* ����: ���ٶ���ʵ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
void dbi_object_delete(dbi_object_t obj);

/*
* ����: dbi_object_statement_compose
* ����: ����sql���
* ����: obj			dbi����
*		statement	���
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_compose(dbi_object_t obj, char *statement);

/*
* ����: dbi_object_statement_composef
* ����: ����sql���
* ����: obj			dbi����
*		fmt			��ʽ�����
*		...			�����б�
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_composef(dbi_object_t obj, char *fmt, ...);

/*
* ����: dbi_object_statement_composef2
* ����: ����sql���
* ����: obj			dbi����
*		fmt			��ʽ�����
*		args		�����б�
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_composef2(dbi_object_t obj, char *fmt, va_list args);

/*
* ����: dbi_object_statement_clear_buf
* ����: ��ȡsql���buf��ָ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
void dbi_object_statement_clear_buf(dbi_object_t obj);

/*
* ����: dbi_object_statement_debug
* ����: �����ǰsql���
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
void dbi_object_statement_debug(dbi_object_t obj);

/*
* ����: dbi_object_statement_get_buf
* ����: ��ȡsql���buf��ָ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
char *dbi_object_statement_get_buf(dbi_object_t obj);

/*
* ����: dbi_object_get_results
* ����: ��ȡ�����
* ����: obj		dbi����
* ����: dbi_results_t
*		- NULL	ʧ��
* ˵��: 
*/
dbi_results_t *dbi_object_get_results(dbi_object_t obj);

#endif


