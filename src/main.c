#include "sys_inc.h"
#include "log_trace.h"
#include "asprintf.h"
#include "dbc.h"
#include "dbi_api_test.h"

/******************************************************************************/
#define TABLE_NAME_1	"COMPANY"
#define TABLE_NAME_2	"COMPANY2"
#define TABLE_NAME_3	"DEPARTMENT"
/******************************************************************************/
dbc_t dbc;
dbi_object_t obj;
/******************************************************************************/
static void _dbc_test_create()
{
	dbc.exec(obj, "CREATE TABLE IF NOT EXISTS %s("
					   "ID INT PRIMARY KEY     NOT NULL,"
					   "NAME           TEXT    NOT NULL,"
					   "AGE            INT     NOT NULL,"
					   "ADDRESS        CHAR(50),"
					   "SALARY         REAL"
					");", TABLE_NAME_1);
	
	dbc.exec(obj, "CREATE TABLE IF NOT EXISTS %s("
					   "ID INT PRIMARY KEY     NOT NULL,"
					   "NAME           TEXT    NOT NULL,"
					   "AGE            INT     NOT NULL,"
					   "ADDRESS        CHAR(50),"
					   "SALARY         REAL"
					");", TABLE_NAME_2);

	dbc.exec(obj, "CREATE TABLE %s("
					   "ID INT PRIMARY KEY      NOT NULL,"
					   "DEPT           CHAR(50) NOT NULL,"
					   "EMP_ID         INT      NOT NULL"
					");", TABLE_NAME_3);
}
/******************************************************************************/
static void _dbc_test_insert()
{
	dbc.insert(obj, TABLE_NAME_1, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		3, "Paul", 32, "California", 20000.00);
	dbc.query(obj);
	
	dbc.insert(obj, TABLE_NAME_1, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		9, "Wade", 35, "New yourk", 10300.00);
	dbc.query(obj);
	
	dbc.insert(obj, TABLE_NAME_1, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		23, "Jame", 34, "Calverrle", 43000.35);
	dbc.query(obj);

	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		24, "Jorzhi", 38, "OKC", 24030.32);
	dbc.query(obj);
	//------------------------------------------
	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		24, "Kobe", 38, "Laker", 28000.00);
	dbc.query(obj);
	
	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		41, "Nowiski", 40, "Moveerelkjr", 500.00);
	dbc.query(obj);
	
	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		21, "Deng", 44, "Spur", 21000.68);
	dbc.query(obj);

	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		56, "Jorry", 28, "Spursdfsdf Spur sdfsdfwefd sdfsdf wefse fdsfc sd dfds f", 12332.68);
	dbc.query(obj);

	//---------------------------------------
	dbc.insert(obj, TABLE_NAME_3, 
		"ID, DEPT, EMP_ID", 
		"%d, '%s', %d", 
		24, "dept_test222", 28);
	dbc.query(obj);
	dbc.insert(obj, TABLE_NAME_3, 
		"ID, DEPT, EMP_ID", 
		"%d, '%s', %d", 
		23, "dept_test32sesdfsdf", 33);
	dbc.query(obj);
}

static void _dbc_test_insertfrom()
{
	dbc.insertfrom(obj, TABLE_NAME_1, "*");
	dbc.select(obj, TABLE_NAME_2, "*", NULL);
	dbc.query(obj);
	//-------------------------
	dbc.insert(obj, TABLE_NAME_2, 
		"ID, NAME, AGE, ADDRESS, SALARY", 
		"%d, '%s', %d, '%s', %f", 
		55, "Simon", 29, "jiangxi ganzhou", 2100.00);
	dbc.query(obj);
	
	dbc.insertfrom(obj, TABLE_NAME_1, "ID, NAME, AGE, ADDRESS, SALARY");
	dbc.select(obj, TABLE_NAME_2, "ID, NAME, AGE, ADDRESS, SALARY", NULL);
	dbc.filter.and(obj, "NAME = '%s'", "Simon");
	dbc.query(obj);
}
/******************************************************************************/
static void _dbc_test_delete()
{
	dbc.delete(obj, TABLE_NAME_2);
	dbc.filter.and(obj, "ID = %d", 56);
	dbc.query(obj);
}
/******************************************************************************/
static void _dbc_test_update()
{
	dbc.update(obj, TABLE_NAME_2, 
		"NAME = '%s', AGE = %d, ADDRESS = '%s', SALARY = %f", 
		"caicaicai", 18, "shenzhen of guandong", 2038.32);
	dbc.filter.and(obj, "ID = %d", 21);
	dbc.query(obj);
}
/******************************************************************************/
static void _dbc_test_select_(const char *tbname)
{
	int id = 0;
	int age = 0;
	float salary = 0.0;
	const char *name = NULL;
	const char *address = NULL;

	int rows = 0;
	int rowidx = 0;
	
	dbc.select(obj, tbname, 
		"ID", "NAME", "AGE", "ADDRESS", "SALARY", NULL);
	dbc.query(obj);

	rows = dbc.result.count(obj);
	dbc_result_foreach(rowidx, rows)
	{
		id = dbc.result.get_int(obj, rowidx, "ID");
		age = dbc.result.get_int(obj, rowidx, "AGE");
		salary = dbc.result.get_float(obj, rowidx, "SALARY");
		name = dbc.result.get_string(obj, rowidx, "NAME");
		address = dbc.result.get_string(obj, rowidx, "ADDRESS");
		LOG_DEBUG_TRACE("%s: %d|%s|%d|%s|%f\n", 
				tbname, id, name, age, address, salary);
	}
	
	dbc.select(obj, tbname, dbc.sql_fun.count("ID"), NULL);
	dbc.query(obj);
	LOG_DEBUG_TRACE("dbc.result.count: %llu\n", dbc.result.count(obj));
	LOG_DEBUG_TRACE("%s: count = %s\n", tbname, 
		dbc.result.get_string_by_colidx(obj, 1, 1));
}

static void _dbc_test_select()
{
	_dbc_test_select_(TABLE_NAME_1);
	_dbc_test_select_(TABLE_NAME_2);
}
/******************************************************************************/
static void _dbc_test_join()
{
	int rows = 0;
	int rowidx = 0;

	int id = 0;
	int age = 0;
	float salary = 0.0;
	const char *name = NULL;
	const char *address = NULL;

	const char *dept = NULL;
	int emp_id = 0;

	dbc.select(obj, TABLE_NAME_1, 
			TABLE_NAME_1".""ID", 
			TABLE_NAME_1".""NAME", 
			TABLE_NAME_1".""AGE", 
			TABLE_NAME_1".""ADDRESS", 
			TABLE_NAME_1".""SALARY",
			TABLE_NAME_3".""DEPT", 
			TABLE_NAME_3".""EMP_ID", NULL);
	dbc.join.inner(obj, TABLE_NAME_3);
	dbc.filter.and(obj, TABLE_NAME_3".ID = "TABLE_NAME_1".ID");
	if (dbc.query(obj) == false)
	{
		return;
	}

	rows = dbc.result.count(obj);
	dbc_result_foreach(rowidx, rows)
	{
		id = dbc.result.get_int(obj, rowidx, "ID");
		age = dbc.result.get_int(obj, rowidx, "AGE");
		salary = dbc.result.get_float(obj, rowidx, "SALARY");
		name = dbc.result.get_string(obj, rowidx, "NAME");
		address = dbc.result.get_string(obj, rowidx, "ADDRESS");

		dept = dbc.result.get_string(obj, rowidx, "DEPT");
		emp_id = dbc.result.get_int(obj, rowidx, "EMP_ID");
		LOG_DEBUG_TRACE("%d|%s|%d|%s|%f <---> %s|%d\n", 
				id, name, age, address, salary, dept, emp_id);
	}
}

/******************************************************************************/
int main(int argc, char **argv)
{
	dbc_sql_args_t dbc_args = {
		.sqltype = E_DBC_SQL_TYPE_SQLITE3,
		.dbdir = ".",
		.dbname = "test.db",
	};
	
	obj = dbi_object_new();
	dbc = dbc_connect(obj, dbc_args);

	LOG_DEBUG_TRACE("*************************************\n");
	
	//建表
	_dbc_test_create();
	LOG_DEBUG_TRACE("*************************************\n");

	//插入
	_dbc_test_insert();
	LOG_DEBUG_TRACE("*************************************\n");

	//查看插入后的表数据
	_dbc_test_select();
	LOG_DEBUG_TRACE("*************************************\n");

	//删除记录
	_dbc_test_delete();
	LOG_DEBUG_TRACE("*************************************\n");

	//查看删除后的表数据
	_dbc_test_select();
	LOG_DEBUG_TRACE("*************************************\n");

	//更新数据
	_dbc_test_update();
	LOG_DEBUG_TRACE("*************************************\n");

	//查看更新后的表数据
	_dbc_test_select();
	LOG_DEBUG_TRACE("*************************************\n");

	//拷贝数据库数据到另外一个数据库
	_dbc_test_insertfrom();

	//查看拷贝后的数据库数据
	_dbc_test_select();
	LOG_DEBUG_TRACE("*************************************\n");

	//join测试
	_dbc_test_join();
	LOG_DEBUG_TRACE("*************************************\n");

	dbc.disconnect(obj);
	dbi_object_delete(obj);
	return 0;
}




