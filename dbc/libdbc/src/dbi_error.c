#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* ����: dbi_error_debug
* ����: ��ӡ��ǰ������Ϣ
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
/*void dbi_error_debug(dbi_object_t obj)
{
	int dbi_errno = 0;
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		dbi_errno = dbi_conn_error(instance->conn, &errmsg);
		LOG_TRACE("dbi_errno: [ %d ], errmsg: [ %s ]\n", dbi_errno, errmsg);
	}
}*/

/*
* ����: dbi_get_errno
* ����: ��ȡ��ǰ�������
* ����: obj		����ʵ��
* ����: int		������
*		- 0		��ʾδ���ִ���
* ˵��: 
*/
const int dbi_get_errno(dbi_object_t obj)
{
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		return dbi_conn_error(instance->conn, &errmsg);
	}

	return 0;
}

/*
* ����: dbi_get_errmsg
* ����: ��ȡ��ǰ������Ϣ
* ����: obj		����ʵ��
* ����: ������Ϣָ��
*		- NULL	�޴�����Ϣ
* ˵��: 
*/
const char *dbi_get_errmsg(dbi_object_t obj)
{
	const char *errmsg;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		dbi_conn_error(instance->conn, &errmsg);
	}

	return errmsg;
}

