#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

/*
* ����: _dbi_driver_set_option
* ����: ���������Ĳ���
* ����: obj		����ʵ��
* ����: bool	
*		- false	ʧ��
*		- true	�ɹ�
* ˵��: 
*/
static bool _dbi_driver_set_option(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance && instance->conn)
	{
		if (strcmp(instance->drivername, "mysql") == 0)
		{
			strcpy(instance->sql_name, "mysql");
			
			dbi_conn_set_option(instance->conn, "host", instance->hostname);
			dbi_conn_set_option(instance->conn, "username", instance->username);
			dbi_conn_set_option(instance->conn, "password", instance->password);
			
			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "sqlite3") == 0)
		{
			strcpy(instance->sql_name, instance->dbname);
			
			if (instance->dbdir 
				&& strlen(instance->dbdir) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"sqlite3_dbdir", instance->dbdir);
			}
			
			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "sqlite") == 0)
		{
			strcpy(instance->sql_name, instance->dbname);
			
			if (instance->dbdir 
				&& strlen(instance->dbdir) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"sqlite_dbdir", instance->dbdir);
			}

			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "pgsql") == 0)
		{
			strcpy(instance->sql_name, "template1");
			
			dbi_conn_set_option(instance->conn, "host", instance->hostname);
			dbi_conn_set_option(instance->conn, "username", instance->username);
			dbi_conn_set_option(instance->conn, "password", instance->password);
			
			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "db2") == 0)
		{
			strcpy(instance->sql_name, "toolsdb");
			
			dbi_conn_set_option(instance->conn, "host", instance->hostname);
			dbi_conn_set_option(instance->conn, "username", instance->username);
			dbi_conn_set_option(instance->conn, "password", instance->password);
			
			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "freetds") == 0)
		{
			strcpy(instance->sql_name, "master");
			
			dbi_conn_set_option(instance->conn, "host", instance->hostname);
			dbi_conn_set_option(instance->conn, "username", instance->username);
			dbi_conn_set_option(instance->conn, "password", instance->password);

			if (strlen(instance->version) > 0)
			{
			   dbi_conn_set_option(instance->conn, 
			   		"freetds_version", instance->version);
			}
			
			if (instance->encoding 
				&& strlen(instance->encoding) > 0)
			{
				dbi_conn_set_option(instance->conn, 
						"encoding", instance->encoding);
			}
		}
		else if (strcmp(instance->drivername, "msql") == 0)
		{
			if (instance->hostname
				&& strlen(instance->hostname) > 0)
			{
				dbi_conn_set_option(instance->conn, 
							"host", instance->hostname);
			}
		}
		else if (strcmp(instance->drivername, "firebird") == 0)
		{
			if (instance->dbdir 
				&& strlen(instance->dbdir) > 0)
			{
				dbi_conn_set_option(instance->conn, "firebird_dbdir", instance->dbdir);
			}
			
			dbi_conn_set_option(instance->conn, "host", instance->hostname);
			dbi_conn_set_option(instance->conn, "username", instance->username);
			dbi_conn_set_option(instance->conn, "password", instance->password);
		}
		else if (strcmp(instance->drivername, "ingres") == 0 
			|| strcmp(instance->drivername, "firebird") == 0)
		{
			strcpy(instance->sql_name, instance->dbname);
		}

		dbi_conn_set_option(instance->conn, "dbname",  instance->dbname);
		dbi_conn_set_option_numeric(instance->conn, 
					"LogQueries", instance->query_log);
		
		return true;
	}

	return false;
}

/*
* ����: dbi_connect_mysql_init
* ����: ����mysql���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
void dbi_connect_mysql_init(
	dbi_object_t obj, const char *hostname, 
	const char *username, const char *password, 
	const char *dbname, const char *encoding)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		snprintf(instance->drivername, 
			sizeof(instance->drivername) - 1, 
			"mysql");
		snprintf(instance->hostname, 
			sizeof(instance->hostname) - 1, 
			"%s", hostname ? hostname : "");
		snprintf(instance->username, 
			sizeof(instance->username) - 1, 
			"%s", username ? username : "");
		snprintf(instance->password, 
			sizeof(instance->password) - 1, 
			"%s", password ? password : "");
		snprintf(instance->dbname, 
			sizeof(instance->dbname) - 1, 
			"%s", dbname ? dbname : "");
		snprintf(instance->encoding, 
			sizeof(instance->encoding) - 1, 
			"%s", encoding ? encoding : "");
	}
}

/*
* ����: dbi_connect_sqlite_init
* ����: ����sqlite���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
void dbi_connect_sqlite_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		snprintf(instance->drivername, 
			sizeof(instance->drivername) - 1, 
			"sqlite");
		snprintf(instance->dbdir, 
			sizeof(instance->dbdir) - 1, 
			"%s", dbdir ? dbdir : "");
		snprintf(instance->dbname, 
			sizeof(instance->dbname) - 1, 
			"%s", dbname ? dbname : "");
	}
}

/*
* ����: dbi_connect_sqlite3_init
* ����: ����sqlite3���ݿ�֮ǰ��Ҫ���һЩ����
* ����: obj		����ʵ��
* ����: ��
* ˵��: 
*/
void dbi_connect_sqlite3_init(dbi_object_t obj, 
	const char *dbdir, const char *dbname)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance)
	{
		snprintf(instance->drivername, 
			sizeof(instance->drivername) - 1, 
			"sqlite3");
		snprintf(instance->dbdir, 
			sizeof(instance->dbdir) - 1, 
			"%s", dbdir ? dbdir : "");
		snprintf(instance->dbname, 
			sizeof(instance->dbname) - 1, 
			"%s", dbname ? dbname : "");
	}
}

/*
* ����: dbi_connect
* ����: ͨ��dbi object�������ݿ�
* ����: obj			dbi����
* ����: bool
*		- false ʧ��
*		- true �ɹ�
* ˵��: �ڵ���dbi_connect֮ǰ������ȵ�����Ӧ��sql conect��ʼ������
*		e.g. 
*			- dbi_connect_mysql_init
*			- dbi_connect_sqlite_init
*			- dbi_connect_sqlite3_init
*/
bool dbi_connect(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL)
	{
		LOG_TRACE("dbi object error!\n");
		return false;
	}

	instance->conn = dbi_conn_new_r(instance->drivername, instance->instance);
	if (instance->conn == NULL)
	{
		LOG_TRACE("dbi_conn_new_r error!\n");
		dbi_error_debug(obj);
		return false;
	}

	_dbi_driver_set_option(obj);

	LOG_TRACE("dbi object connecting ...\n");
	if (dbi_conn_connect(instance->conn) < 0)
	{
		LOG_TRACE("could not connect, please check the option settings!\n");
		dbi_error_debug(obj);
		return false;
	}
	LOG_TRACE("dbi object connection successful.\n");

	return true;
}

/*
* ����: dbi_disconnect
* ����: ͨ��dbi object�Ͽ��������ݿ�
* ����: obj			dbi����
* ����: bool
*		- false ʧ��
*		- true �ɹ�
* ˵��: 
*/
bool dbi_disconnect(dbi_object_t obj)
{
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL)
	{
		LOG_TRACE("dbi object error!\n");
		return false;
	}

	if (instance->result)
	{
		dbi_result_free(instance->result);
		instance->result = NULL;
	}
	
	if (instance->conn)
	{	
		dbi_conn_close(instance->conn);
		instance->conn = NULL;
	}

	return true;
}

/*
* ����: dbi_connection_is_alive
* ����: �ж������Ƿ�����
* ����: obj		dbi����
* ����: bool
*		- false ���ӿ��ܶϿ�
*		- true	��������
* ˵��: ��ping�������׼ȷ��
*/
bool dbi_connection_is_alive(dbi_object_t obj)
{	
	dbi_instance_t *instance = (dbi_instance_t *) obj;
	if (instance == NULL 
		|| instance->conn == NULL)
	{
		LOG_TRACE("%s\n", 
			instance == NULL ? "dbi object null!" : 
			instance->conn == NULL ? "dbi object not yet connection!" : "");
		return false;
	}

	return (bool) dbi_conn_ping(instance->conn);
}

