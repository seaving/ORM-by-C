#ifndef __DBI_CONNECT_H__
#define __DBI_CONNECT_H__

#include "dbi_object.h"

/*
* ����: dbi_connect_mysql_init
* ����: ����mysql���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
*		hostname	���ݿ�������ַ
*		username	���ݿ��û���
*		password	���ݿ�����
*		dbname		���ݿ�����
*		encoding	����
* ����: ��
* ˵��: 
*/
void dbi_connect_mysql_init(
	dbi_object_t obj, const char *hostname, 
	const char *username, const char *password, 
	const char *dbname, const char *encoding);

/*
* ����: dbi_connect_sqlite_init
* ����: ����sqlite���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
*		dbdir	sqlite���ݿ�·��
*		dbname	sqlite���ݿ�����
* ����: ��
* ˵��: 
*/
void dbi_connect_sqlite_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname);

/*
* ����: dbi_connect_sqlite3_init
* ����: ����sqlite3���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
*		dbdir	sqlite���ݿ�·��
*		dbname	sqlite���ݿ�����
* ����: ��
* ˵��: 
*/
void dbi_connect_sqlite3_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname);

/*
* ����: dbi_connect
* ����: ͨ��dbi object�������ݿ�
* ����: obj			dbi����
*		sql_name	���ݿ����� - mysql postgresql sqlite3
*		host		���ݿ�������ַ
*		username	���ݿ��û���
*		password	���ݿ�����
*		dbname		���ݿ�����
*		encoding	����
* ����: bool
*		- false ʧ��
*		- true �ɹ�
* ˵��: �ڵ���dbi_connect֮ǰ������ȵ�����Ӧ��sql conect��ʼ������
*		e.g. 
*			- dbi_connect_mysql_init
*			- dbi_connect_sqlite_init
*			- dbi_connect_sqlite3_init
*/
bool dbi_connect(dbi_object_t obj);

/*
* ����: dbi_disconnect
* ����: ͨ��dbi object�Ͽ��������ݿ�
* ����: obj			dbi����
* ����: bool
*		- false ʧ��
*		- true �ɹ�
* ˵��: 
*/
bool dbi_disconnect(dbi_object_t obj);

/*
* ����: dbi_connection_is_alive
* ����: �ж������Ƿ�����
* ����: obj		dbi����
* ����: bool
*		- false ���ӿ��ܶϿ�
*		- true	��������
* ˵��: ��ping�������׼ȷ��
*/
bool dbi_connection_is_alive(dbi_object_t obj);

#endif


