#include "sys_inc.h"
#include "log_trace.h"
#include "asprintf.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* ����: _dbi_result_free
* ����: ����dbi_result
* ����: obj		����ʵ��
* ����: ��
* ˵��: ÿ������resultһ��Ҫ�ǵû���
*/
static inline void _dbi_result_free(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->result)
	{
		dbi_result_free(instance->result);
		instance->result = NULL;
	}
}

/*
* ����: dbi_query
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
*		sql		sql����ַ���
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: 
*/
dbi_results_t dbi_query(dbi_object_t obj, const char *sql)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	LOG_DEBUG_TRACE("---->>> %s\n\n", sql);

	_dbi_result_free(obj);
	instance->result = dbi_conn_query(instance->conn, sql);
	
	return instance->result;
}

/*
* ����: dbi_query_by_statement_buf
* ����: ִ��sql��䲢���ؽ��
* ����: obj		dbi����
* ����: dbi_results_t	�������
*		- NULL ִ��ʧ��
* ˵��: sql�����Դ��obj��Աstatement
*/
dbi_results_t dbi_query_by_statement_buf(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	LOG_DEBUG_TRACE("---->>> %s\n\n", instance->statement);
	
	_dbi_result_free(obj);
	instance->result = dbi_conn_query(instance->conn, instance->statement);
	dbi_object_statement_clear_buf(obj);
	
	return instance->result;
}

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
dbi_results_t dbi_queryf(dbi_object_t obj, const char *sql_fmt, ...)
{
	dbi_results_t results = NULL;
	va_list ap;
	va_start(ap, sql_fmt);
	results = dbi_queryf2(obj, sql_fmt, ap);
	va_end(ap);

	return results;
}

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
dbi_results_t dbi_queryf2(dbi_object_t obj, const char *sql_fmt, va_list args)
{
	char *sql = NULL;

	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	vasprintf(&sql, sql_fmt, args);
	_dbi_result_free(obj);
	if (sql)
	{
		LOG_DEBUG_TRACE("---->>> %s\n\n", sql);

		instance->result = dbi_conn_query(instance->conn, sql);
		free(sql);
	}

	return instance->result;
}

/*
* ����: dbi_query_db_list
* ����: ��ѯ���ݿ��б�
* ����: obj		dbi����
*		pattern	SQL������ʽ��Ϊ�����ѯ���п���
* ����: dbi_results_t	�������
*		- NULL ��ѯʧ��
* ˵��: 
*/
dbi_results_t dbi_query_db_list(dbi_object_t obj, const char *pattern)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL || instance->conn == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return NULL;
	}

	_dbi_result_free(obj);
	instance->result = dbi_conn_get_db_list(instance->conn, pattern);

	return instance->result;
}

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
	const char *db, const char *pattern)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL 
		|| instance->conn == NULL 
		|| db == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : 
			db == NULL ? "db is null!" : "");
		return NULL;
	}

	_dbi_result_free(obj);
	instance->result = dbi_conn_get_table_list(instance->conn, db, pattern);

	return instance->result;
}

/*
* ����: dbi_switches_db
* ����: �л����ݿ�
* ����: obj		dbi����
*		db		���ݿ�
* ����: bool
*		- false ʧ��
* ˵��: 
*/
bool dbi_switches_db(dbi_object_t obj, const char *db)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL 
		|| instance->conn == NULL 
		|| db == NULL)
	{
		LOG_DEBUG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : 
			db == NULL ? "db is null!" : "");
		return false;
	}

	return dbi_conn_select_db(instance->conn, db);
}




