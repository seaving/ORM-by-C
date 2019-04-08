#include "includes.h"

#include "dbi_object.h"
#include "dbi_connect.h"
#include "dbi_query.h"
#include "dbi_result_row.h"
#include "dbi_result_field.h"
#include "dbi_error.h"
#include "dbi_misc.h"

#include "sql_sqlite3.h"

/*
* ����: _dbc_exec
* ����: ִ��sql
* ����: obj 			����ʵ��
*		sql_fmt 		sql����ַ���
*		... 			��ʽ�������б�
* ����: bool
*		- false ʧ��
* ˵��: ֱ������ִ��sql���ķ���
*/
static bool _dbc_exec(dbi_object_t obj, const char *sql_fmt, ...)
{
	dbi_results_t result = NULL;
	va_list ap;
	if (obj == DBI_OBJECT_NULL 
		|| sql_fmt == NULL)
	{
		return false;
	}

	va_start(ap, sql_fmt);
	result = dbi_queryf2(obj, sql_fmt, ap);
	va_end(ap);

	return result ? true : false;
}

/*
* ����: _dbc_result_gets
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj		dbi object
*		rowidx	�ڼ��У���1��ʼ
*		fmt 	��ʽ���ַ���������printf������ʽ
*		args 	��ʽ�������б����ڱ����ȡ����ֵ
* ����: unsigned int	��ȡ�ɹ��ֶ�����
*		- 0 			ʧ��
* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
*		... Ϊ�ɱ������ÿ���������α������ȡ��ַ���� &
*		����: _dbc_result_gets(row, "name.%s sex.%s age.%d", &name, &sex, &age)
*	--- ��ʽ�ַ�:
*		%c / %uc: char / unsigned char
*		%h / %uh: short / unsigned short
*		%l / %ul: int / unsigned int(long��intһ��)
*		%i / %ui: int / unsigned int(long��intһ��)
*		%L / %uL: long long / unsigned long long
*		%f: float
*		%d: double
*		%s: string
*		%b: unsigned char * �������ַ���
*		%t: time_t ��ʾ���ں�/��ʱ���ʱ��ֵ
*/
static unsigned int _dbc_result_gets(
	dbi_object_t obj, unsigned int rowidx, const char *fmt, ...)
{
	unsigned int ret = 0;
	va_list ap;
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| fmt == NULL)
	{
		return 0;
	}

	va_start(ap, fmt);
	dbi_result_row_seek(results, rowidx);
	ret = dbi_result_field_get_values2(results, fmt, ap);
	va_end(ap);
	return ret;
}

/*
* ����: _dbc_result_get_char
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: char
* ˵��: 
*/
static char _dbc_result_get_char(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_char_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_uchar
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: unsigned char
* ˵��: 
*/
static unsigned char _dbc_result_get_uchar(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uchar_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_short
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: short
* ˵��: 
*/
static short _dbc_result_get_short(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_short_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_ushort
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: unsigned short
* ˵��: 
*/
static unsigned short _dbc_result_get_ushort(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ushort_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_int
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: int
* ˵��: 
*/
static int _dbc_result_get_int(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_int_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_uint
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: unsigned int
* ˵��: 
*/
static unsigned int _dbc_result_get_uint(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uint_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_long
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: long
* ˵��: 
*/
static long _dbc_result_get_long(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_long_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_ulong
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: unsigned long
* ˵��: 
*/
static unsigned long _dbc_result_get_ulong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulong_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_longlong
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: long long
* ˵��: 
*/
static long long _dbc_result_get_longlong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_longlong_value_by_fieldname(results, field);
	}

	return 0L;
}

/*
* ����: _dbc_result_get_ulonglong
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: unsigned long long
* ˵��: 
*/
static unsigned long long _dbc_result_get_ulonglong(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulonglong_value_by_fieldname(results, field);
	}

	return 0L;
}

/*
* ����: _dbc_result_get_float
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: float
* ˵��: 
*/
static float _dbc_result_get_float(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_float_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_double
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: double
* ˵��: 
*/
static double _dbc_result_get_double(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_double_value_by_fieldname(results, field);
	}

	return 0;
}

/*
* ����: _dbc_result_get_string
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: const char *
* ˵��: 
*/
static const char *_dbc_result_get_string(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_string_value_by_fieldname(results, field);
	}

	return NULL;
}

/*
* ����: _dbc_result_get_binary
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: const unsigned char *
* ˵��: 
*/
static const unsigned char *_dbc_result_get_binary(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_binary_value_by_fieldname(results, field);
	}

	return NULL;
}

/*
* ����: _dbc_result_get_datetime
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		field	�ֶ���
* ����: time_t
* ˵��: 
*/
static time_t _dbc_result_get_datetime(dbi_object_t obj, 
			unsigned int rowidx, const char *field)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| field == NULL)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_datetime_value_by_fieldname(results, field);
	}

	return 0;
}


/*
* ����: _dbc_result_get_char_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: char
* ˵��: 
*/
static char _dbc_result_get_char_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_char_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_uchar_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: unsigned char
* ˵��: 
*/
static unsigned char _dbc_result_get_uchar_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uchar_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_short_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: short
* ˵��: 
*/
static short _dbc_result_get_short_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_short_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_ushort_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: unsigned short
* ˵��: 
*/
static unsigned short _dbc_result_get_ushort_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ushort_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_int_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: int
* ˵��: 
*/
static int _dbc_result_get_int_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_int_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_uint_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: unsigned int
* ˵��: 
*/
static unsigned int _dbc_result_get_uint_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_uint_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_long_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: long
* ˵��: 
*/
static long _dbc_result_get_long_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_long_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_ulong_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: unsigned long
* ˵��: 
*/
static unsigned long _dbc_result_get_ulong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulong_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_longlong_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: long long
* ˵��: 
*/
static long long _dbc_result_get_longlong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_longlong_value_by_idx(results, columnidx);
	}

	return 0L;
}

/*
* ����: _dbc_result_get_ulonglong_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: unsigned long long
* ˵��: 
*/
static unsigned long long _dbc_result_get_ulonglong_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0L;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_ulonglong_value_by_idx(results, columnidx);
	}

	return 0L;
}

/*
* ����: _dbc_result_get_float_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: float
* ˵��: 
*/
static float _dbc_result_get_float_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_float_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_double_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: double
* ˵��: 
*/
static double _dbc_result_get_double_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_double_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_get_string_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: const char *
* ˵��: 
*/
static const char *_dbc_result_get_string_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_string_value_by_idx(results, columnidx);
	}

	return NULL;
}

/*
* ����: _dbc_result_get_binary_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: const unsigned char *
* ˵��: 
*/
static const unsigned char *_dbc_result_get_binary_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return NULL;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_binary_value_by_idx(results, columnidx);
	}

	return NULL;
}

/*
* ����: _dbc_result_get_datetime_by_colidx
* ����: ��row��������ȡ�ֶε�ֵ
* ����: obj 	dbi object
*		rowidx	�ڼ��У���1��ʼ
*		columnidx	�кţ���1��ʼ
* ����: time_t
* ˵��: 
*/
static time_t _dbc_result_get_datetime_by_colidx(dbi_object_t obj, 
			unsigned int rowidx, unsigned int columnidx)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL
		|| rowidx <= 0 
		|| columnidx <= 0)
	{
		return 0;
	}

	if (dbi_result_row_seek(results, rowidx))
	{
		return dbi_result_get_datetime_value_by_idx(results, columnidx);
	}

	return 0;
}

/*
* ����: _dbc_result_count
* ����: ��ȡ��ǰ���������������
* ����: obj			dbi ����
* ����: unsigned long long	����
* ˵��: 
*/
static unsigned long long _dbc_result_count(dbi_object_t obj)
{
	dbi_results_t results = dbi_object_get_results(obj);
	if (results == NULL)
	{
		return 0;
	}

	return dbi_result_get_rows_count(results);
}

/*
* ����: dbc_connect
* ����: �������ݿ�
* ����: obj		����ʵ��
*		args	һЩ���ݿ���صĲ����������������ݿ���Ҫ�Ĳ���
* ����: dbc_t	����һ��dbc����
* ˵��: args�ṹ������Ĳ����������ж�Ҫ��ֵ��������ݿⲻͬ���������Ҳ��ͬ
*		����mysql���ݿ��õ�����username password hostname����sqlite3�õ�����
*		��dbdir��dbname
*		ʹ�÷���:
*			��sqlite3Ϊ��:
*			dbc_sql_args_t sql_args = {.dbdir="", .dbname=""};
*			dbc_connect(obj, sql_args);
*		ֱ�Ӷ���һ��args�������ҳ�ʼ��ֵ���ٽ��д��Σ�����Ҫָ�������
*		����ֻ���������ݲ������ѣ��Ȿ����Ƶĳ���
*/
dbc_t dbc_connect(dbi_object_t obj, dbc_sql_args_t args)
{
	bool sqltype_flag = true;
	dbc_t dbc;

	memset(&dbc, 0, sizeof(dbc_t));
	
	switch (args.sqltype)
	{
		case E_DBC_SQL_TYPE_SQLITE:
			//dbc = sqlite;
			//dbi_connect_sqlite_init(obj, args.dbdir, args.dbname);
			//break;
		case E_DBC_SQL_TYPE_SQLITE3:
			dbc = sqlite3;
			dbi_connect_sqlite3_init(obj, args.dbdir, args.dbname);
			break;
		case E_DBC_SQL_TYPE_MYSQL:
			//dbc = mysql;
			//dbi_connect_mysql_init(
			//	obj, args.hostname, args.username, 
			//	args.password, args.dbname, args.encoding);
		default:
			LOG_TRACE("Not support SQL: %d\n", args.sqltype);
			sqltype_flag = false;
			break;
	}
	
	if (sqltype_flag == false)
	{
		return dbc;
	}
#define set_fun(c, f) \
	do { \
		if (c == NULL) \
		{ \
			c = f; \
		} \
	} while (0)

	set_fun(dbc.exec, _dbc_exec);

	set_fun(dbc.result.gets, _dbc_result_gets);

	set_fun(dbc.result.get_char, _dbc_result_get_char);
	set_fun(dbc.result.get_uchar, _dbc_result_get_uchar);
	set_fun(dbc.result.get_short, _dbc_result_get_short);
	set_fun(dbc.result.get_ushort, _dbc_result_get_ushort);
	set_fun(dbc.result.get_int, _dbc_result_get_int);
	set_fun(dbc.result.get_uint, _dbc_result_get_uint);
	set_fun(dbc.result.get_long, _dbc_result_get_long);
	set_fun(dbc.result.get_ulong, _dbc_result_get_ulong);
	set_fun(dbc.result.get_longlong, _dbc_result_get_longlong);
	set_fun(dbc.result.get_ulonglong, _dbc_result_get_ulonglong);
	set_fun(dbc.result.get_float, _dbc_result_get_float);
	set_fun(dbc.result.get_double, _dbc_result_get_double);
	set_fun(dbc.result.get_string, _dbc_result_get_string);
	set_fun(dbc.result.get_binary, _dbc_result_get_binary);
	set_fun(dbc.result.get_datetime, _dbc_result_get_datetime);

	set_fun(dbc.result.get_char_by_colidx, _dbc_result_get_char_by_colidx);
	set_fun(dbc.result.get_uchar_by_colidx, _dbc_result_get_uchar_by_colidx);
	set_fun(dbc.result.get_short_by_colidx, _dbc_result_get_short_by_colidx);
	set_fun(dbc.result.get_ushort_by_colidx, _dbc_result_get_ushort_by_colidx);
	set_fun(dbc.result.get_int_by_colidx, _dbc_result_get_int_by_colidx);
	set_fun(dbc.result.get_uint_by_colidx, _dbc_result_get_uint_by_colidx);
	set_fun(dbc.result.get_long_by_colidx, _dbc_result_get_long_by_colidx);
	set_fun(dbc.result.get_ulong_by_colidx, _dbc_result_get_ulong_by_colidx);
	set_fun(dbc.result.get_longlong_by_colidx, _dbc_result_get_longlong_by_colidx);
	set_fun(dbc.result.get_ulonglong_by_colidx, _dbc_result_get_ulonglong_by_colidx);
	set_fun(dbc.result.get_float_by_colidx, _dbc_result_get_float_by_colidx);
	set_fun(dbc.result.get_double_by_colidx, _dbc_result_get_double_by_colidx);
	set_fun(dbc.result.get_string_by_colidx, _dbc_result_get_string_by_colidx);
	set_fun(dbc.result.get_binary_by_colidx, _dbc_result_get_binary_by_colidx);
	set_fun(dbc.result.get_datetime_by_colidx, _dbc_result_get_datetime_by_colidx);
	
	set_fun(dbc.result.count, _dbc_result_count);

	if (dbi_connect(obj) == false)
	{
		LOG_TRACE("dbi connect sql error!\n");
	}

	return dbc;
#undef set_fun
}

