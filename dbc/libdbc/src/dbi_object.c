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
* ����: dbi_object_new
* ����: ��������ʵ��
* ����: ��
* ����: dbi����
*		- 0		ʧ��
* ˵��: 
*/
dbi_object_t dbi_object_new()
{
	int ret = -1;
	dbi_instance_t *instance = NULL;
	instance = calloc(sizeof(dbi_instance_t), 1);
	if (instance == NULL)
	{
		LOG_DEBUG_PERROR("calloc error!\n");
		return (dbi_object_t) NULL;
	}

	ret = dbi_initialize_r("/usr/local/lib/dbd", &instance->instance);
	if (ret < 0)
	{
		LOG_DEBUG_TRACE("unable to initialize libdbi! "
			"make sure you specified a valid driver directory.\n");
		dbi_object_delete((dbi_object_t) instance);
		return (dbi_object_t) NULL;
	}

	if (instance->instance == NULL)
	{
		LOG_DEBUG_TRACE("dbi_initialize_r error!\n");
		dbi_object_delete((dbi_object_t) instance);
		return (dbi_object_t) NULL;
	}

	return (dbi_object_t) instance;
}

/*
* ����: dbi_object_delete
* ����: ���ٶ���ʵ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
void dbi_object_delete(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		if (instance->result)
		{
			dbi_result_free(instance->result);
		}
		if (instance->conn)
		{
			dbi_conn_close(instance->conn);
		}
		if (instance->instance)
		{
			dbi_shutdown_r(instance->instance);
		}
		free(instance);
	}
}

/*
* ����: dbi_object_statement_compose
* ����: ����sql���
* ����: obj			dbi����
*		statement	���
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_compose(dbi_object_t obj, char *statement)
{
	int ret = 0;
	int size = 0;
	int offset = 0;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		size = sizeof(instance->statement);
		offset = strlen(instance->statement);
		ret = snprintf(instance->statement + offset, 
				size - offset - 1, "%s", statement);
	}

	return ret;
}

/*
* ����: dbi_object_statement_composef
* ����: ����sql���
* ����: obj			dbi����
*		fmt			��ʽ�����
*		...			�����б�
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_composef(dbi_object_t obj, char *fmt, ...)
{
	int ret = 0;
	int size = 0;
	int offset = 0;
	char *result;
	va_list ap;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && fmt)
	{
		va_start(ap, fmt);
		vasprintf(&result, fmt, ap);
		va_end(ap);
		if (result)
		{
			size = sizeof(instance->statement);
			offset = strlen(instance->statement);
			ret = snprintf(instance->statement + offset, 
					size - offset - 1, "%s%s", 
					instance->statement[offset - 1 < 0 ? 0 : offset - 1] 
							== ' ' ? "" : " ", result);
			free(result);
		}
	}

	return ret;
}

/*
* ����: dbi_object_statement_composef2
* ����: ����sql���
* ����: obj			dbi����
*		fmt			��ʽ�����
*		args		�����б�
* ����: int		��ǰ����
* ˵��: 
*/
int dbi_object_statement_composef2(dbi_object_t obj, char *fmt, va_list args)
{
	int ret = 0;
	int size = 0;
	int offset = 0;
	char *result;
	va_list ap;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && fmt)
	{
		va_copy(ap, args);
		vasprintf(&result, fmt, ap);
		va_end(ap);
		if (result)
		{
			size = sizeof(instance->statement);
			offset = strlen(instance->statement);
			ret = snprintf(instance->statement + offset, 
					size - offset - 1, "%s%s", 
					instance->statement[offset - 1 < 0 ? 0 : offset - 1] 
							== ' ' ? "" : " ", result);
			free(result);
		}
	}

	return ret;
}

/*
* ����: dbi_object_statement_clear_buf
* ����: ���sql���buf��ָ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
void dbi_object_statement_clear_buf(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		memset(instance->statement, 0, sizeof(instance->statement));
	}
}

/*
* ����: dbi_object_statement_get_buf
* ����: ��ȡsql���buf��ָ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
char *dbi_object_statement_get_buf(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		return instance->statement;
	}

	return NULL;
}

/*
* ����: dbi_object_get_results
* ����: ��ȡ�����
* ����: obj		dbi����
* ����: dbi_results_t
*		- NULL	ʧ��
* ˵��: 
*/
dbi_results_t *dbi_object_get_results(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		return instance->result;
	}

	return NULL;
}

