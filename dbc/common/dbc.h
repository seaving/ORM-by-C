/********************************************************************************
* @File name: dbc.h
* @Author: caixiwen
* @Date: 2019-4-6
* @Description: The function interface
*

dbc(database container���ݿ�����)�������������ݿ�Ĳ���������װ���ˣ�ʹ����ͳһ��
dbc���������ݿ⣬����ǿ���ڲ�ʹ�õ��Ǻ������ݿ�

     app
      |
     dbc
      |
sqlite3 mysql ...
      |
  dbi object
      |
    libdbi
********************************************************************************/
#ifndef __DBC_H__
#define __DBC_H__

typedef intptr_t dbi_object_t;
/******************************************************************************/

typedef enum __dbc_sql_type__
{
	E_DBC_SQL_TYPE_SQLITE = 0,
	E_DBC_SQL_TYPE_SQLITE3,
	E_DBC_SQL_TYPE_MYSQL,
	E_DBC_SQL_TYPE_UNKOWN
} dbc_sql_type_t;

typedef struct __dbc_sql_args_
{
	dbc_sql_type_t sqltype;
	const char *hostname;
	const char *username;
	const char *password;
	const char *dbdir;
	const char *dbname;
	const char *encoding;
	const char *version;
} dbc_sql_args_t;
/******************************************************************************/
#define CHARPOINT char*
typedef struct __dbc_sql_fun__
{
	/*
	* ����: sum
	* ����: ���ܣ�����Ҳ�ǹ����ַ���
	* ����: field		��ͳ�Ƶ��ֶ�
	* ����: char *
	*		- NULL		ʧ��
	* ˵��: ���selectʹ��
	*/
	const CHARPOINT (*sum)(const char *field);
	/*
	* ����: count
	* ����: ͳ������������Ҳ�ǹ����ַ���
	* ����: field		��ͳ�Ƶ��ֶ�
	* ����: char *
	*		- NULL		ʧ��
	* ˵��: ���selectʹ��
	*/
	const CHARPOINT (*count)(const char *field);
	/*
	* ����: distinct
	* ����: ȥ�أ�����Ҳ�ǹ����ַ���
	* ����: field		ȥ���ֶ�
	* ����: char *
	*		- NULL		ʧ��
	* ˵��: ���selectʹ��
	*/
	const CHARPOINT (*distinct)(const char *field);
} dbc_sql_fun_t;

/******************************************************************************/
typedef struct __dbc_result__
{
	/*
	* ����: gets
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		fmt 	��ʽ���ַ���������printf������ʽ
	*		args	��ʽ�������б����ڱ����ȡ����ֵ
	* ����: unsigned int	��ȡ�ɹ��ֶ�����
	*		- 0 			ʧ��
	* ˵��: fmt ��ʽ: "fieldname1.%ul fieldname2.%s fieldname3.%s"
	*				fmt�ַ����б�����[�ֶ���.��ʽ����ʶ]������ֶ�֮���ÿո����
	*		... Ϊ�ɱ������ÿ���������α������ȡ��ַ���� &
	*		����: gets(row, "name.%s sex.%s age.%d", &name, &sex, &age)
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
	unsigned int (*gets)(dbi_object_t obj, 
				unsigned int rowidx, const char *fmt, ...);

	/*
	* ����: get_char
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: char
	* ˵��: 
	*/
	char (*get_char)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_uchar
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: unsigned char
	* ˵��: 
	*/
	unsigned char (*get_uchar)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_short
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: short
	* ˵��: 
	*/
	short (*get_short)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_ushort
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: unsigned short
	* ˵��: 
	*/
	unsigned short (*get_ushort)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_int
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: int
	* ˵��: 
	*/
	int (*get_int)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_uint
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: unsigned int
	* ˵��: 
	*/
	unsigned int (*get_uint)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_long
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: long
	* ˵��: 
	*/
	long (*get_long)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_ulong
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: unsigned long
	* ˵��: 
	*/
	unsigned long (*get_ulong)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_longlong
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: long long
	* ˵��: 
	*/
	long long (*get_longlong)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_ulonglong
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: unsigned long long
	* ˵��: 
	*/
	unsigned long long (*get_ulonglong)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_float
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: float
	* ˵��: 
	*/
	float (*get_float)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_double
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: double
	* ˵��: 
	*/
	double (*get_double)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_string
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: const char *
	* ˵��: 
	*/
	const CHARPOINT (*get_string)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_binary
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: const unsigned char *
	* ˵��: 
	*/
	const unsigned CHARPOINT (*get_binary)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_datetime
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		field 	�ֶ���
	* ����: time_t
	* ˵��: 
	*/
	time_t (*get_datetime)(dbi_object_t obj, 
				unsigned int rowidx, const char *field);

	/*
	* ����: get_char_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: char
	* ˵��: 
	*/
	char (*get_char_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_uchar_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: unsigned char
	* ˵��: 
	*/
	unsigned char (*get_uchar_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_short_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: short
	* ˵��: 
	*/
	short (*get_short_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_ushort_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: unsigned short
	* ˵��: 
	*/
	unsigned short (*get_ushort_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_int_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: int
	* ˵��: 
	*/
	int (*get_int_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_uint_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: unsigned int
	* ˵��: 
	*/
	unsigned int (*get_uint_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_long_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: long
	* ˵��: 
	*/
	long (*get_long_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_ulong_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: unsigned long
	* ˵��: 
	*/
	unsigned long (*get_ulong_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_longlong_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: long long
	* ˵��: 
	*/
	long long (*get_longlong_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_ulonglong_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: unsigned long long
	* ˵��: 
	*/
	unsigned long long (*get_ulonglong_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_float_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: float
	* ˵��: 
	*/
	float (*get_float_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_double_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: double
	* ˵��: 
	*/
	double (*get_double_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_string_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: const char *
	* ˵��: 
	*/
	const CHARPOINT (*get_string_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_binary_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: const unsigned char *
	* ˵��: 
	*/
	const unsigned CHARPOINT (*get_binary_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: get_datetime_by_colidx
	* ����: ��row��������ȡ�ֶε�ֵ
	* ����: obj		dbi object
	*		rowidx	�ڼ��У���1��ʼ
	*		columnidx 	�кţ���1��ʼ
	* ����: time_t
	* ˵��: 
	*/
	time_t (*get_datetime_by_colidx)(dbi_object_t obj, 
				unsigned int rowidx, unsigned int columnidx);

	/*
	* ����: count
	* ����: ��ȡ��ǰ���������������
	* ����: obj			dbi ����
	* ����: unsigned long long	����
	* ˵��: 
	*/
	unsigned long long (*count)(dbi_object_t obj);

} dbc_result_t;
/******************************************************************************/
typedef struct __dbc_filter__
{
	/*
	* ����: and
	* ����: ����������sql����е�AND����
	*		�ú����Զ����AND���ϣ�����Ҫ�û�����
	*		�û�ֻ��Ҫ�����ַ�������ʽ����������
	* ����: obj 			����ʵ��
	*		condition_fmt 	��������ʽ��
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �涨conditionֻ����һ���ж����
	*	e.g. and(obj, "name != 'jorry'")
	*	e.g. and(obj, "age > 20")
	*	e.g. and(obj, "age == %d", age)
	*/
	bool (*and)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* ����: or
	* ����: ����������sql����е�OR����
	*		�ú����Զ����OR���ϣ�����Ҫ�û�����
	*		�û�ֻ��Ҫ�����ַ�������ʽ����������
	* ����: obj 			����ʵ��
	*		condition_fmt 	��������ʽ��
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �涨conditionֻ����һ���ж����
	*	e.g. or(obj, "name != 'jorry'")
	*	e.g. or(obj, "age > 20")
	*	e.g. or(obj, "age == %d", age)
	*/
	bool (*or)(dbi_object_t obj, char *condition_fmt, ...);
	/*
	* ����: limit
	* ����: ����������sql����е�LIMIT OFFSET����
	* ����: obj 			����ʵ��
	*		offset 			ƫ�Ƶ��ڼ���
	*		limit_ 			��offset+limit_�н���
	* ����: bool
	*		- false ʧ��
	* ˵��: �ú������selectʹ��
	*/
	bool (*limit)(dbi_object_t obj, unsigned int offset, unsigned int limit_);
	/*
	* ����: sort
	* ����: ����������sql����е�order by����-����
	* ����: obj 			����ʵ��
	*		fields 			Ҫ������ֶΣ�����ֶζ��Ÿ���
	*		asc				Ϊtrue��ʾ����false����
	* ����: bool
	*		- false ʧ��
	* ˵��: �ú������selectʹ��
	*/
	bool (*sort)(dbi_object_t obj, const char *fields, bool asc);
	/*
	* ����: group
	* ����: ����������sql����е�group by����-����
	* ����: obj 			����ʵ��
	*		fields 			�����ֶΣ�����ֶζ��Ÿ���
	* ����: bool
	*		- false ʧ��
	* ˵��: �ú������selectʹ��
	*/
	bool (*group)(dbi_object_t obj, const char *fields);
} dbc_filter_t;
/******************************************************************************/
typedef struct __dbc__
{
	//-------------------------------------
	dbc_sql_fun_t sql_fun;
	dbc_result_t result;
	dbc_filter_t filter;
	//-------------------------------------
	/*
	* ����: disconnect
	* ����: �Ͽ����Ӳ���
	* ����: obj 		����ʵ��
	* ����: bool
	*		- false ʧ��
	* ˵��: 
	*/
	bool (*disconnect)(dbi_object_t obj);
	/*
	* ����: exec
	* ����: ִ��sql
	* ����: obj 			����ʵ��
	*		sql_fmt			sql����ַ���
	*		...				��ʽ�������б�
	* ����: bool
	*		- false ʧ��
	* ˵��: ֱ������ִ��sql���ķ���
	*/
	bool (*exec)(dbi_object_t obj, const char *sql_fmt, ...);
	/*
	* ����: query
	* ����: ִ��sql
	* ����: obj 			����ʵ��
	* ����: bool
	*		- false ʧ��
	* ˵��: ִ�����е�insert��delete��update��select��sql����������
	*		�������յ���query�������������ݿ�����ִ��sql�������ҷ��ؽ��
	*/
	bool (*query)(dbi_object_t obj);
	/*
	* ����: insert
	* ����: �������
	* ����: obj 			����ʵ��
	*		tbname			����
	*		fields			�ֶ��б�
	*		values_fmt		ֵ�б�
	*		... 			�����б�
	* ����: bool
	*		- false ʧ��
	* ˵��: �ֶ��б����ַ�����ʽ: "field1, field2, field3, field4" �ö��Ÿ���
	*		ֵ�б����ַ�����ʽ: "value1, value2, value3, value4" �ö��Ÿ���
	*		ֵ�б��������ֵ���ַ������������''�ţ�Ҫ���sql����ʽ
	*/
	bool (*insert)(dbi_object_t obj, const char *tbname, 
					const char *fields, const char *values_fmt, ...);
	/*
	* ����: delete
	* ����: ɾ������
	* ����: obj 			����ʵ��
	*		tbname			����
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*/
	bool (*delete)(dbi_object_t obj, const char *tbname);
	/*
	* ����: update
	* ����: ���²���
	* ����: obj 			����ʵ��
	*		tbname			������
	*		set_fmt			�ֶθ�ֵ��ʽ�����
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*		set_fmt ��ʽ���sql�﷨��"field1=value1, field2='value2', field3='value3'"
	*/
	bool (*update)(dbi_object_t obj, const char *tbname, const char *set_fmt, ...);
	/*
	* ����: select
	* ����: ��ѯ����
	* ����: obj 			����ʵ��
	*		tbname			������
	*		field1			Ҫ��ѯ���ֶΣ�*�ű�ʾ�����ֶ�
	*		... 			�ֶ��б�
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*		�ɱ�����б������NULL��β�����������ڴ����
	*		select(obj, taname, "field1", "field2", "count(name)", NULL);
	*/
	bool (*select)(dbi_object_t obj, const char *tbname, const char *field1, ...);
} dbc_t;
#undef CHARPOINT
/******************************************************************************/

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
dbc_t dbc_connect(dbi_object_t obj, dbc_sql_args_t args);

/*
* ����: dbi_object_new
* ����: ��������ʵ��
* ����: ��
* ����: dbi����
*		- 0		ʧ��
* ˵��: 
*/
extern dbi_object_t dbi_object_new();

/*
* ����: dbi_object_delete
* ����: ���ٶ���ʵ��
* ����: obj		dbi����
* ����: ��
* ˵��: 
*/
extern void dbi_object_delete(dbi_object_t obj);

#endif


