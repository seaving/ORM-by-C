/********************************************************************************
* @File name: sql_sqlite3.h
* @Author: caixiwen
* @Date: 2019-4-6
* @Description: The function interface
*

�����: sql_sqlite3_t	ͨ���ṹ�巽�����⿪��API��������C++��namespace��class��װ����
�м��: sql_sqlite3.c	�ṩ���ݿ����Ĺ����װ��Ϊÿһ�����ݿ����(insert, select
						delete, update��)��Ϲ�����(and or limit order by��)������������
						���յ���query����ִ��
�ײ�: 	dbi_object		��װ�˶Դ󲿷����ݿ��api������ͳһ�ӿ�
********************************************************************************/

#ifndef __SQL_SQLITE_3_H__
#define __SQL_SQLITE_3_H__

#include "dbi_object.h"

/******************************************************************************/
typedef struct __sql_sqlite3_filter__
{
	/*
	* ����: and
	* ����: ����������sql����е�AND����
	*		�ú����Զ����AND���ϣ�����Ҫ�û�����
	*		�û�ֻ��Ҫ�����ַ�������ʽ����������
	* ����: obj 			����ʵ��
	*		condition_fmt 	��������ʽ��
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �涨conditionֻ����һ���ж����
	*	e.g. and(obj, "name != 'jorry'")
	*	e.g. and(obj, "age > 20")
	*	e.g. and(obj, "age == %d", age)
	*/
	bool (*and)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* ����: or
	* ����: ����������sql����е�OR����
	*		�ú����Զ����OR���ϣ�����Ҫ�û�����
	*		�û�ֻ��Ҫ�����ַ�������ʽ����������
	* ����: obj 			����ʵ��
	*		condition_fmt 	��������ʽ��
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �涨conditionֻ����һ���ж����
	*	e.g. or(obj, "name != 'jorry'")
	*	e.g. or(obj, "age > 20")
	*	e.g. or(obj, "age == %d", age)
	*/
	bool (*or)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* ����: limit
	* ����: ����������sql����е�LIMIT OFFSET����
	* ����: obj 			����ʵ��
	*		offset 			ƫ�Ƶ��ڼ���
	*		limit_ 			��offset+limit_�н���
	* ����: bool
	*		- false ʧ��
	* ˵��: �ú������selectʹ��
	*/
	bool (*limit)(dbi_object_t obj, unsigned int offset, unsigned int limit_);
} sql_sqlite3_filter_t;
/******************************************************************************/
typedef struct __sql_sqlite3__
{
	sql_sqlite3_filter_t filter;
	//-------------------------------------
	/*
	* ����: _sql_sqlite3_connect
	* ����: ���Ӳ���
	* ����: obj 		����ʵ��
	*		dbdir		���ݿ�·��
	*		dbname		���ݿ�����
	* ����: bool
	*		- false ʧ��
	* ˵��: 
	*/
	bool (*connect)(dbi_object_t obj, const char *dbdir, const char *dbname);
	/*
	* ����: disconnect
	* ����: �Ͽ����Ӳ���
	* ����: obj 		����ʵ��
	* ����: bool
	*		- false ʧ��
	* ˵��: 
	*/
	bool (*disconnect)(dbi_object_t obj);
	/*
	* ����: query
	* ����: ִ��sql
	* ����: obj 			����ʵ��
	* ����: bool
	*		- false ʧ��
	* ˵��: ִ�����е�insert��delete��update��select��sql����������
	*		�������յ���query�������������ݿ�����ִ��sql�������ҷ��ؽ��
	*/
	bool (*query)(dbi_object_t obj);
	/*
	* ����: insert
	* ����: �������
	* ����: obj 			����ʵ��
	*		tbname			����
	*		fields			�ֶ��б�
	*		values_fmt		ֵ�б�
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �ֶ��б����ַ�����ʽ: "field1, field2, field3, field4" �ö��Ÿ���
	*		ֵ�б����ַ�����ʽ: "value1, value2, value3, value4" �ö��Ÿ���
	*		ֵ�б��������ֵ���ַ������������''�ţ�Ҫ���sql����ʽ
	*/
	bool (*insert)(dbi_object_t obj, const char *tbname, 
					const char *fields, const char *values_fmt, ...);
	/*
	* ����: delete
	* ����: ɾ������
	* ����: obj 			����ʵ��
	*		tbname			����
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*/
	bool (*delete)(dbi_object_t obj, const char *tbname);
	/*
	* ����: update
	* ����: ���²���
	* ����: obj 			����ʵ��
	*		tbname			������
	*		set_fmt			�ֶθ�ֵ��ʽ�����
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*		set_fmt ��ʽ���sql�﷨��"field1=value1, field2='value2', field3='value3'"
	*/
	bool (*update)(dbi_object_t obj, const char *tbname, const char *set_fmt);
	/*
	* ����: select
	* ����: ��ѯ����
	* ����: obj 			����ʵ��
	*		tbname			������
	*		fields			Ҫ��ѯ���ֶΣ�*�ű�ʾ�����ֶ�
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*		field ��ʽ���sql�﷨��"field1, field2, field3"���ö��Ÿ���
	*/
	bool (*select)(dbi_object_t obj, const char *tbname, const char *fields);
} sql_sqlite3_t;
/******************************************************************************/

extern sql_sqlite3_t sqlite3;

#endif

