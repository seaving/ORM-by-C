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

int dbi_api_test()
{
	const char *fieldname = NULL;
	bool ret = false;
	int i = 0;
	unsigned int n = 0;
	unsigned int loop_cnt = 0;
	dbi_results_t results = NULL;

	dbi_results_t result = NULL;
	const char *name = "caixiwen";
	dbi_result_bind_string(result, "name", &name);
	
	LOG_TRACE("count = %llu\n", dbi_result_get_rows_count(result));
	return 0;
	
	dbi_object_t obj = dbi_object_new();
	if (obj == 0)
	{
		goto exit;
	}

	dbi_driver_list_debug(obj);

	dbi_connect_sqlite3_init(obj, ".", "test.db");
	if (dbi_connect(obj) == false)
	{
		goto exit;
	}

	results = dbi_query_db_list(obj, NULL);
	if (results == NULL)
	{
		LOG_TRACE("result was null!\n");
		dbi_error_debug(obj);
		goto exit;
	}
	LOG_TRACE("result rows count: %llu\n", dbi_result_get_rows_count(results));


	results = dbi_queryf(obj, "CREATE TABLE COMPANY("
							   "ID INT PRIMARY KEY     NOT NULL,"
							   "NAME           TEXT    NOT NULL,"
							   "AGE            INT     NOT NULL,"
							   "ADDRESS        CHAR(50),"
							   "SALARY         REAL"
							");");

	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (1, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (3, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (4, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (5, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (6, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (7, 'Allen', 25, 'Texas', 15000.00 );");
	results = dbi_queryf(obj, "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
					"VALUES (8, 'Alsdfsdfsdlen', 225, 'sdfsdfsdfsd', 153400.00 );");
	if (results == NULL)
	{
		LOG_TRACE("INSERT error!\n");
		dbi_error_debug(obj);
		//goto exit;
	}
	
	results = dbi_queryf(obj, "SELECT * FROM COMPANY");
	if (results == NULL)
	{
		LOG_TRACE("result was null!\n");
		dbi_error_debug(obj);
		//goto exit;
	}

	LOG_TRACE("result rows count: %llu\n", dbi_result_get_rows_count(results));
	LOG_TRACE("-------------------------------\n");

	if (dbi_result_row_add(results, 
			"ID.%i NAME.%s AGE.%i ADDRESS.%s SALARY.%f", 
				100, "caixiwen", 29, "shenzhen", 0.0) == false)
	{
		LOG_TRACE("dbi_result_row_add error!\n");
		dbi_error_debug(obj);
	}
	LOG_TRACE("result rows count: %llu\n", dbi_result_get_rows_count(results));
	LOG_TRACE("-------------------------------\n");

	loop_cnt = 0;
	dbi_result_row_foreach(results)
	{
		LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
		n = dbi_result_field_get_length_by_fieldname(results, "ADDRESS");
		LOG_TRACE("dbi_result_field_get_length_by_fieldname: %u\n", n);
		n = dbi_result_field_get_length_by_idx(results, 4);
		LOG_TRACE("dbi_result_field_get_length_by_idx: %u\n", n);
		n = dbi_result_field_get_idx(results, "ADDRESS");
		LOG_TRACE("dbi_result_field_get_idx: %u\n", n);
		for (i = 1; i <= dbi_result_field_get_count(results); i ++)
		{
			fieldname = dbi_result_field_get_name(results, i);
			LOG_TRACE("field name: %s\n", fieldname);
			LOG_TRACE("field type by name: %u\n", 
					dbi_result_field_get_type_by_fieldname(results, fieldname));
			LOG_TRACE("field type by idx: %u\n", 
					dbi_result_field_get_type_by_idx(results, 
					dbi_result_field_get_idx(results, fieldname)));
		}
		
		loop_cnt ++;
		if (loop_cnt > 3)
			break;
	}
	LOG_TRACE("-------------------------------\n");
	LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
	if (dbi_result_row_seek_to_first(results) == false)
	{
		dbi_error_debug(obj);
	}
	LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
	LOG_TRACE("-------------------------------\n");
	
	dbi_result_row_foreach_from(ret, results, 2)
	{
		LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
		for (i = 1; i <= dbi_result_field_get_count(results); i ++)
		{
			fieldname = dbi_result_field_get_name(results, i);
			if (i == 1) LOG_TRACE("value - %s: %d\n", fieldname, dbi_result_get_int_value_by_fieldname(results, fieldname)); 
			if (i == 2) LOG_TRACE("value - %s: %s\n", fieldname, dbi_result_get_string_value_by_fieldname(results, fieldname)); 
			if (i == 3) LOG_TRACE("value - %s: %d\n", fieldname, dbi_result_get_int_value_by_fieldname(results, fieldname)); 
			if (i == 4) LOG_TRACE("value - %s: %s\n", fieldname, dbi_result_get_string_value_by_fieldname(results, fieldname)); 
			if (i == 5) LOG_TRACE("value - %s: %f\n", fieldname, dbi_result_get_float_value_by_fieldname(results, fieldname)); 
		}
	}
	LOG_TRACE("-------------------------------\n");
	LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
	LOG_TRACE("-------------------------------\n");

	dbi_result_row_foreach_limit(ret, loop_cnt, results, 2, 5)
	{
		int id = 0;
		char *name = NULL;
		LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
		dbi_result_field_get_values(results, "ID.%i NAME.%s", &id, &name);
		LOG_TRACE("id: %d, NAME: %s\n", id, name);
	}
	LOG_TRACE("-------------------------------\n");
	LOG_TRACE("--- %llu\n", dbi_result_get_currow_idx(results));
	LOG_TRACE("result rows count: %llu\n", dbi_result_get_rows_count(results));

exit:
	dbi_object_delete(obj);
	return 0;
}


