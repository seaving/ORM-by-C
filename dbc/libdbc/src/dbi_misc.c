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
* ����: dbi_driver_list_debug
* ����: ���֧�ֵ������б�
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
void dbi_driver_list_debug(dbi_object_t obj)
{
	dbi_driver drviers = NULL;
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->instance)
	{
	   	while ((drviers = dbi_driver_list_r(
	   				drviers, instance->instance)) != NULL)
	   	{
	      	LOG_TRACE("%s\n", dbi_driver_get_name(drviers));
	   	}
   	}
}








