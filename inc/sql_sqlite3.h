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

#include "dbc.h"

extern dbc_t sqlite3;

#endif

