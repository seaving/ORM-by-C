#include "includes.h"

/*
* ����: dbc_connect
* ����: �������ݿ�
* ����: obj		����ʵ��
*		args	һЩ���ݿ���صĲ����������������ݿ���Ҫ�Ĳ���
* ����: dbc_t	����һ��dbc����
* ˵��: args�ṹ������Ĳ����������ж�Ҫ��ֵ��������ݿⲻͬ���������Ҳ��ͬ
*		����mysql���ݿ��õ�����username password hostname����sqlite3�õ�����
*		��dbdir��dbname
*		ʹ�÷���:
*			��sqlite3Ϊ��:
*			dbc_sql_args_t sql_args = {.dbdir="", .dbname=""};
*			dbc_connect(obj, sql_args);
*		ֱ�Ӷ���һ��args�������ҳ�ʼ��ֵ���ٽ��д��Σ�����Ҫָ�������
*		����ֻ���������ݲ������ѣ��Ȿ����Ƶĳ���
*/
dbc_t dbc_connect(dbi_object_t obj, dbc_sql_args_t args)
{
	dbc_t dbc;

	memset(&dbc, 0, sizeof(dbc_t));
	
	switch (args.sqltype)
	{
		case E_DBC_SQL_TYPE_SQLITE:
			//dbc = sqlite;
			//dbi_connect_sqlite_init(obj, args.dbdir, args.dbname);
			//break;
		case E_DBC_SQL_TYPE_SQLITE3:
			dbc = sqlite3;
			dbi_connect_sqlite3_init(obj, args.dbdir, args.dbname);
			break;
		case E_DBC_SQL_TYPE_MYSQL:
			//dbc = mysql;
			//dbi_connect_mysql_init(
			//	obj, args.hostname, args.username, 
			//	args.password, args.dbname, args.encoding);
		default:
			LOG_TRACE("Not support SQL: %d\n", args.sqltype);
			break;
	}
	
	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
}


