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
} dbc_filter_t;
/******************************************************************************/
typedef struct __dbc__
{
	//-------------------------------------
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
	bool (*update)(dbi_object_t obj, const char *tbname, const char *set_fmt);
	/*
	* ����: select
	* ����: ��ѯ����
	* ����: obj 			����ʵ��
	*		tbname			������
	*		fields			Ҫ��ѯ���ֶΣ�*�ű�ʾ�����ֶ�
	* ����: bool
	*		- false ʧ��
	* ˵��: ���filter���ṩ�ķ�����������
	*		field ��ʽ���sql�﷨��"field1, field2, field3"���ö��Ÿ���
	*/
	bool (*select)(dbi_object_t obj, const char *tbname, const char *fields);
} dbc_t;
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


