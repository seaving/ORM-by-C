#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

#include "sql_sqlite3.h"

/*
* ����: _dbc_result_gets
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj		dbi object
*		rowidx	�ڼ��У���1��ʼ
*		fmt 	��ʽ���ַ���������printf������ʽ
*		args 	��ʽ�������б����ڱ����ȡ����ֵ
* ����: unsigned int	��ȡ�ɹ��ֶ�����
*		- 0 			ʧ��
* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
*		... Ϊ�ɱ������ÿ���������α������ȡ��ַ���� &
*		����: _dbc_result_gets(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
static unsigned int _dbc_result_gets(
	dbi_object_t obj, unsigned int rowidx, const char *fmt, ...)
{
	unsigned int ret = 0;
	va_list ap;
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| fmt == NULL)
	{
		return 0;
	}

	va_start(ap, fmt);
	dbi_result_row_seek(results, rowidx);
	ret = dbi_result_field_get_values2(results, fmt, ap);
	va_end(ap);
	return ret;
}

/*
* ����: _dbc_result_count
* ����: ��ȡ��ǰ���������������
* ����: obj			dbi ����
* ����: unsigned long long	����
* ˵��: 
*/
static unsigned long long _dbc_result_count(dbi_object_t obj)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL)
	{
		return 0;
	}

	return dbi_result_get_rows_count(results);
}

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
	bool sqltype_flag = true;
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
			sqltype_flag = false;
			break;
	}
	
	if (sqltype_flag == false)
	{
		return dbc;
	}

	dbc.result.gets = _dbc_result_gets;
	dbc.result.count = _dbc_result_count;
	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
}

