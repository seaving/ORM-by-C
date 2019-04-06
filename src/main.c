#include "includes.h"

int main(int argc, char **argv)
{
	//dbi_api_test();

	dbi_object_t obj = dbi_object_new();

	sqlite3.connect(obj, ".", "test.db");

	sqlite3.insert(obj, "iot_bas_alminfoext", 
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
	sqlite3.query(obj);

	sqlite3.select(obj, "iot_bas_alminfoext", "upperlimit1_exist, upperlimit1");
	sqlite3.filter.and(obj, "upperlimit1_exist = 5");
	sqlite3.filter.and(obj, "upperlimit2 = %f", 1.2);
	sqlite3.filter.or(obj, "delta = %f", 2.5);
	sqlite3.filter.limit(obj, 2, 5);
	sqlite3.query(obj);

	sqlite3.disconnect(obj);
	dbi_object_delete(obj);
	return 0;
}



