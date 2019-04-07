#include "includes.h"
#include "dbi_api_test.h"

dbc_t dbc;

int main(int argc, char **argv)
{
	dbc_sql_args_t dbc_args = {
		.sqltype = E_DBC_SQL_TYPE_SQLITE3,
		.dbdir = ".",
		.dbname = "test.db",
	};
	
	dbi_object_t obj = dbi_object_new();
	dbc = dbc_connect(obj, dbc_args);

	dbc.insert(obj, "iot_bas_alminfoext", 
			"device_type, device_model, mete_type, report_level, "
			"upperlimit1_exist, upperlimit1, upperlimit2_exist, upperlimit2, "
			"lowerlimit2_exist, lowerlimit2, upperlimit3_exist, upperlimit3, "
			"lowerlimit3_exist, lowerlimit3, upperlimit4_exist, upperlimit4, "
			"lowerlimit4_exist, lowerlimit4, delayAlarm_time, "
			"delayCancelAlarm_time, delta", 
			"%d, %d, %d, %d, "
			"%d, %f, %d, %f, "
			"%d, %f, %d, %f, "
			"%d, %f, %d, %f, "
			"%d, %f, %d, %d, %f", 
			121, 2, 323, 4, 
			5, 1.2, 5, 1.2, 
			5, 1.2, 5, 1.2, 
			5, 1.2, 5, 1.2, 
			5, 1.2, 10, 15, 2.5);
	dbc.query(obj);

	dbc.select(obj, "iot_bas_alminfoext", "upperlimit1_exist, upperlimit1");
	dbc.filter.and(obj, "upperlimit1_exist = 5");
	dbc.filter.and(obj, "upperlimit2 = %f", 1.2);
	dbc.filter.or(obj, "delta = %f", 2.5);
	dbc.filter.limit(obj, 2, 5);
	dbc.query(obj);

	int upperlimit1_exist = 0;
	float upperlimit1 = 0;
	dbc.result.gets(obj, 1, "upperlimit1_exist.%i upperlimit1.%f", 
			&upperlimit1_exist, &upperlimit1);

	LOG_TRACE("count = %llu\n", dbc.result.count(obj));
	LOG_TRACE("%d|%f\n", upperlimit1_exist, upperlimit1);
	
	dbc.disconnect(obj);
	dbi_object_delete(obj);
	return 0;
}




