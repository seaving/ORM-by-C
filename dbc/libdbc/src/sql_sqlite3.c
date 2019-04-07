#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"


/******************************************************************************/
static bool _sql_sqlite3_and(dbi_object_t obj, char *condition_fmt, ...);
static bool _sql_sqlite3_or(dbi_object_t obj, char *condition_fmt, ...);

static bool _sql_sqlite3_limit(dbi_object_t obj, 
						unsigned int offset, unsigned int limit);

static bool _sql_sqlite3_query(dbi_object_t obj);

static bool _sql_sqlite3_insert(dbi_object_t obj, const char *tbname, 
						const char *fields, const char *values_fmt, ...);

static bool _sql_sqlite3_delete(dbi_object_t obj, const char *tbname);

static bool _sql_sqlite3_update(dbi_object_t obj, 
							const char *tbname, const char *set_fmt);

static bool _sql_sqlite3_select(dbi_object_t obj, 
							const char *tbname, const char *fields);
/******************************************************************************/
dbc_t sqlite3 = {
	.filter = {
		.and = _sql_sqlite3_and,
		.or = _sql_sqlite3_or,
		.limit = _sql_sqlite3_limit,
	},
	.disconnect = dbi_disconnect,
	.query = _sql_sqlite3_query,
	.insert = _sql_sqlite3_insert,
	.delete = _sql_sqlite3_delete,
	.update = _sql_sqlite3_update,
	.select = _sql_sqlite3_select,
};
/******************************************************************************/
/*
* ����: _sql_sqlite3_and
* ����: ����������sql����е�AND����
*		�ú����Զ����AND���ϣ�����Ҫ�û�����
*		�û�ֻ��Ҫ�����ַ�������ʽ����������
* ����: obj 			����ʵ��
*		condition_fmt	��������ʽ��
*		... 			�����б�
* ����: bool
*		- false ʧ��
* ˵��: �涨conditionֻ����һ���ж����
*	e.g. _sql_sqlite3_and(obj, "name != 'jorry'")
*	e.g. _sql_sqlite3_and(obj, "age > 20")
*	e.g. _sql_sqlite3_and(obj, "age == %d", age)
*/
static bool _sql_sqlite3_and(dbi_object_t obj, char *condition_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| condition_fmt == NULL)
	{
		return false;
	}

	len = strlen(condition_fmt);
	if (len <= 0)
	{
		return false;
	}
	
	len += 10;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}
	
	va_start(ap, condition_fmt);
	snprintf(sql, len, "AND %s", condition_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);

	return true;
}

/*
* ����: _sql_sqlite3_or
* ����: ����������sql����е�OR����
*		�ú����Զ����OR���ϣ�����Ҫ�û�����
*		�û�ֻ��Ҫ�����ַ�������ʽ����������
* ����: obj 			����ʵ��
*		condition_fmt	��������ʽ��
*		... 			�����б�
* ����: bool
*		- false ʧ��
* ˵��: �涨conditionֻ����һ���ж����
*	e.g. _sql_sqlite3_or(obj, "name != 'jorry'")
*	e.g. _sql_sqlite3_or(obj, "age > 20")
*	e.g. _sql_sqlite3_or(obj, "age == %d", age)
*/
static bool _sql_sqlite3_or(dbi_object_t obj, char *condition_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| condition_fmt == NULL)
	{
		return false;
	}
	
	len = strlen(condition_fmt);
	if (len <= 0)
	{
		return false;
	}
	len += 10;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}

	va_start(ap, condition_fmt);
	snprintf(sql, len, "OR %s", condition_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);
	
	return true;
}
/*
* ����: _sql_sqlite3_limit
* ����: ����������sql����е�LIMIT OFFSET����
* ����: obj 			����ʵ��
*		offset			ƫ�Ƶ��ڼ���
*		limit_			��offset+limit_�н���
* ����: bool
*		- false ʧ��
* ˵��: �ú������selectʹ��
*/
static bool _sql_sqlite3_limit(dbi_object_t obj, 
	unsigned int offset, unsigned int limit)
{
	if (obj == DBI_OBJECT_NULL)
	{
		return false;
	}

	dbi_object_statement_composef(obj, "LIMIT %u OFFSET %u", limit, offset);
	return true;
}

/******************************************************************************/
/*
* ����: _sql_sqlite3_query
* ����: ִ��sql
* ����: obj 			����ʵ��
* ����: bool
*		- false ʧ��
* ˵��: ִ�����е�insert��delete��update��select��sql����������
*		�������յ���query�������������ݿ�����ִ��sql�������ҷ��ؽ��
*/
static bool _sql_sqlite3_query(dbi_object_t obj)
{
	if (obj == DBI_OBJECT_NULL)
	{
		return false;
	}

	if (dbi_query_by_statement_buf(obj) == false)
	{
		dbi_error_debug(obj);
		return false;
	}

	return true;
}
/******************************************************************************/
/*
* ����: _sql_sqlite3_insert
* ����: �������
* ����: obj 			����ʵ��
*		tbname			����
*		fields			�ֶ��б�
*		values_fmt		ֵ�б�
*		...				�����б�
* ����: bool
*		- false ʧ��
* ˵��: �ֶ��б����ַ�����ʽ: "field1, field2, field3, field4" �ö��Ÿ���
*		ֵ�б����ַ�����ʽ: "value1, value2, value3, value4" �ö��Ÿ���
*		ֵ�б��������ֵ���ַ������������''�ţ�Ҫ���sql����ʽ
*/
static bool _sql_sqlite3_insert(
	dbi_object_t obj, const char *tbname, 
	const char *fields, const char *values_fmt, ...)
{
	int len = 0;
	char *sql = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL
		|| tbname == NULL 
		|| fields == NULL 
		|| values_fmt == NULL)
	{
		return false;
	}
	
	len = strlen(fields) + strlen(values_fmt);
	if (len <= 0)
	{
		return false;
	}
	
	len += 64;
	sql = calloc(1, len + 1);
	if (sql == NULL)
	{
		LOG_TRACE("calloc error!\n");
		return false;
	}

	snprintf(sql, len, 
		"INSERT INTO %s (%s) VALUES (%s)", 
		tbname, fields, values_fmt);

	va_start(ap, values_fmt);
	dbi_object_statement_composef2(obj, sql, ap);
	va_end(ap);

	free(sql);

	return true;
}

/*
* ����: _sql_sqlite3_delete
* ����: ���²���
* ����: obj 			����ʵ��
*		tbname			������
*		set_fmt 		�ֶθ�ֵ��ʽ�����
* ����: bool
*		- false ʧ��
* ˵��: ���filter���ṩ�ķ�����������
*		set_fmt ��ʽ���sql�﷨��"field1=value1, field2='value2', field3='value3'"
*/
static bool _sql_sqlite3_delete(
	dbi_object_t obj, const char *tbname)
{
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL)
	{
		return false;
	}

	dbi_object_statement_composef(obj, "DELETE FROM %s WHERE 1=1", tbname);
	return true;
}

/*
* ����: _sql_sqlite3_update
* ����: ��������
* ����: obj				����ʵ��
*		tbname			������
*		set_fmt			�ֶθ�ֵ��ʽ�����
* ����: bool
*		- false ʧ��
* ˵��: set_fmt���sql�﷨
*/
static bool _sql_sqlite3_update(
	dbi_object_t obj, const char *tbname, 
	const char *set_fmt)
{
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL)
	{
		return false;
	}

	dbi_object_statement_composef(
		obj, "UPDATE %s SET %s WHERE 1=1", 
			tbname, set_fmt);

	return true;
}

/*
* ����: _sql_sqlite3_select
* ����: ��ѯ����
* ����: obj 			����ʵ��
*		tbname			������
*		fields			Ҫ��ѯ���ֶΣ�*�ű�ʾ�����ֶ�
* ����: bool
*		- false ʧ��
* ˵��: ���filter���ṩ�ķ�����������
*		field ��ʽ���sql�﷨��"field1, field2, field3"���ö��Ÿ���
*/
static bool _sql_sqlite3_select(
	dbi_object_t obj, const char *tbname, 
	const char *fields)
{
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL)
	{
		return false;
	}

	dbi_object_statement_composef(
		obj, "SELECT %s FROM %s WHERE 1=1", 
			fields, tbname);

	return true;
}

