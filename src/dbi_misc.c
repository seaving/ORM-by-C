#include "includes.h"


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








