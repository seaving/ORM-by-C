#include "includes.h"


/*
* 函数: dbi_driver_list_debug
* 功能: 输出支持的驱动列表
* 参数: obj		对象实例
* 返回: 无
* 说明: 
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








