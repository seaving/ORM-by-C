#ifndef __DBI_ERROR_H__
#define __DBI_ERROR_H__

#include "log_trace.h"
#include "dbi_object.h"

/*
* ����: dbi_error_debug
* ����: ��ӡ��ǰ������Ϣ
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
#define dbi_error_debug(obj) \
	do { \
		int dbi_errno = 0; \
		const char *errmsg; \
		dbi_instance_t *instance = (dbi_instance_t *) obj; \
		if (instance && instance->conn) \
		{ \
			dbi_errno = dbi_conn_error(instance->conn, &errmsg); \
			LOG_TRACE("dbi_errno: [ %d ], errmsg: [ %s ]\n", dbi_errno, errmsg); \
		} \
	} while (0);

/*
* ����: dbi_error_debug
* ����: ��ӡ��ǰ������Ϣ
* ����: obj		����ʵ��
* ����: ��
* ˵��: ���񵽵���Ϣ�ǵ�ǰ���������Ĵ�����Ϣ��������errno
*/
//void dbi_error_debug(dbi_object_t obj);

/*
* ����: dbi_get_errno
* ����: ��ȡ��ǰ�������
* ����: obj		����ʵ��
* ����: int		������
*		- 0		��ʾδ���ִ���
* ˵��: ���񵽵���Ϣ�ǵ�ǰ���������Ĵ�����Ϣ��������errno
*/
const int dbi_get_errno(dbi_object_t obj);

/*
* ����: dbi_get_errmsg
* ����: ��ȡ��ǰ������Ϣ
* ����: obj		����ʵ��
* ����: ������Ϣָ��
*		- NULL	�޴�����Ϣ
* ˵��: ���񵽵���Ϣ�ǵ�ǰ���������Ĵ�����Ϣ��������errno
*/
const char *dbi_get_errmsg(dbi_object_t obj);


#endif


