#if 0

#include "includes.h"

static dbi_object_t _dbi_obj = DBI_OBJECT_NULL;

static dbi_object_t _hub_database_open_sqlite3(
	const char *dbdir, const char *dbname)
{
	dbi_results_t result = NULL;
	dbi_object_t obj = DBI_OBJECT_NULL;
	if (dbdir == NULL 
		|| dbname == NULL)
	{
		return DBI_OBJECT_NULL;
	}
	
	obj = dbi_object_new();
	if (obj == DBI_OBJECT_NULL)
	{
		return DBI_OBJECT_NULL;
	}
	
	dbi_connect_sqlite3_init(obj, dbdir, dbname);
	if (dbi_connect(obj) == false)
	{
		dbi_object_delete(obj);
		return DBI_OBJECT_NULL;
	}

	result = dbi_queryf(obj, "PRAGMA foreign_keys = ON");
	if (result == NULL)
	{
		dbi_error_debug(obj);
		dbi_object_delete(obj);
		return DBI_OBJECT_NULL;
	}

	result = dbi_queryf(obj, "ATTACH '%s%sdevicebase.db' as devicebase;", 
				dbdir, dbdir[strlen(dbdir) - 1] == '/' ? "" : "/");
	if (result == NULL)
	{
		dbi_error_debug(obj);
		dbi_object_delete(obj);
		return DBI_OBJECT_NULL;
	}

	return obj;
}

static void _hub_database_close(dbi_object_t obj)
{
	if (obj == DBI_OBJECT_NULL)
	{
		return;
	}

	dbi_object_delete(obj);
}

static bool _hub_database_cloum_add(
	dbi_object_t obj, const char *tbname, 
	const char *cloumname, const char *type)
{
	dbi_results_t result = NULL;
	
	if (obj == DBI_OBJECT_NULL 
		|| tbname == NULL 
		|| cloumname == NULL 
		|| type == NULL)
	{
		return false;
	}

	result = dbi_queryf(obj, 
		"SELECT %s FROM %s LIMIT 1;", 
		cloumname, tbname);
	if (result)
	{
		return true;
	}

	result = dbi_queryf(obj, 
		"ALTER TABLE %s ADD COLUMN %s %s;", 
		tbname, cloumname, type);
	if (result)
	{
		return true;
	}

	return false;
}

static bool _hub_database_create(dbi_object_t obj)
{
	dbi_results_t result = NULL;

	const char *value = NULL;
	char tbversion[6] = {0};
	char tbversion2[6] = {0};

	if (obj == DBI_OBJECT_NULL)
	{
		return false;
	}

#define dbi_get_value(results, fieldname, vb) \
	do { \
		dbi_result_row_foreach(results) \
		{ \
			value = dbi_result_get_string_value_by_fieldname(result, fieldname); \
			if (value) \
			{ \
				snprintf(vb, sizeof(vb) - 1, "%s", value); \
			} \
			break; \
		} \
	} while (0)

#define access_query(ret, is_return) \
	do { \
		if (ret == false) \
		{ \
			dbi_error_debug(obj); \
			if (is_return) \
			{ \
				return false; \
			} \
		} \
	} while (0)

	access_query(dbi_queryf(obj, IOT_BAS_VERSION_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_BAS_DEVICE_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_CFG_AUTO_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_CFG_TRIGGER_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_CFG_ACTION_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_BAS_ALMINFOEXT_TB_CREATE_SQL), true);
	access_query(dbi_queryf(obj, IOT_HIS_DEVICEALARM_TB_CREATE_SQL), true);

	_hub_database_cloum_add(obj, IOT_CFG_ACTION_TB, "sub_ruleId", "INT");
	_hub_database_cloum_add(obj, IOT_BAS_VERSION_TB, "createTime", "INT");

	result = access_query(
				dbi_queryf(obj, 
					"SELECT major FROM %s LIMIT 1;", 
					IOT_BAS_VERSION_TB), 
				false);
	dbi_get_value(result, "major", tbversion);

	result = access_query(
				dbi_queryf(obj, "SELECT major FROM "
					"devicebase.iot_bas_version;"), 
				false);
	dbi_get_value(result, "major", tbversion2);
	if (strncmp(tbversion2, tbversion, strlen(tbversion)) != 0)
	{
		access_query(
				dbi_queryf(obj, 
					"DELETE FROM %s WHERE rowid != 0;", 
					IOT_BAS_ALMINFOEXT_TB), 
				false);
		access_query(
				dbi_queryf(obj, "UPDATE %s SET UpdateTime = "
					"datetime('now', 'localtime'), %s where %s;", 
					IOT_BAS_VERSION_TB, "major", tbversion), 
				false);
		access_query(
				dbi_queryf(obj, "INSERT INTO iot_bas_alminfoext "
					"SELECT * FROM devicebase.iot_bas_alminfoext;"), 
				false);
	}
	if (tbversion[0] == '\0')
	{
		access_query(
			dbi_queryf(obj, "INSERT INTO %s(major, minor, description) "
				"VALUES('%s', '%s', '%s');", IOT_BAS_VERSION_TB, 
				DATABASE_MAJOR, DATABASE_MINOR, "base model"), 
			false);
		access_query(
			dbi_queryf(obj, "DELETE FROM %s WHERE rowid != 0;", 
				IOT_BAS_ALMINFOEXT_TB), 
			false);
		access_query(
			dbi_queryf(obj, "INSERT INTO %s "
				"SELECT * FROM devicebase.iot_bas_alminfoext;", 
				IOT_BAS_ALMINFOEXT_TB), 
			false);
	}
	
	return true;
#undef dbi_get_value
#undef access_query
}

#endif

