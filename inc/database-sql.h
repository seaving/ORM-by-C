#if 0
#ifndef __DATABASE_SQL_H__
#define __DATABASE_SQL_H__

#include "hal_device.h"
#include "automode.h"
#include "devices_alarm.h"


#define KEYIDLEN						33

#define DATABASE_NAME 						"/etc/IoT/devicehub.db"
#define DATABASE_MAJOR 						"1.0"
#define DATABASE_MINOR 						"0"

#define IOT_BAS_VERSION_TB					"iot_bas_version"
//#define IOT_BAS_DEVICEKIND_TB				"iot_bas_devicekind"
//#define IOT_BAS_DEVICETYPE_TB				"iot_bas_devicetype"
//#define IOT_BAS_DEVICEMODEL_TB			"iot_bas_devicemodel"
#define IOT_BAS_DEVICE_TB					"iot_bas_device"
//#define IOT_BAS_TELEADJUST_TB				"iot_bas_teleadjust"
//#define IOT_BAS_TELESIGNAL_TB				"iot_bas_telesignal"
#define IOT_CFG_AUTO_TB						"iot_cfg_auto"
#define IOT_CFG_TRIGGER_TB					"iot_cfg_trigger"
#define IOT_CFG_ACTION_TB					"iot_cfg_action"

#define IOT_HIS_DEVICEALARM_TB				"iot_his_devicealarm"
#define IOT_BAS_ALMINFOEXT_TB				"iot_bas_alminfoext"
#define IOT_BAS_DEVICE_METEVALUE_TB			"iot_bas_device_metevalue"

/**********************************************************************************************************************/
#define IOT_BAS_VERSION_TB_CREATE_SQL		"CREATE TABLE IF NOT EXISTS "IOT_BAS_VERSION_TB" " \
											"(major VARCHAR(10) PRIMARY KEY," \
											"minor VARCHAR(10)," \
											"description VARCHAR(40)," \
											"UpdateTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime')));"
/**********************************************************************************************************************/
#define IOT_BAS_DEVICE_TB_CREATE_SQL		"CREATE TABLE IF NOT EXISTS "IOT_BAS_DEVICE_TB" " \
											"(deviceId CHAR(16) PRIMARY KEY," \
											"device_name VARCHAR(16)," \
											"module_name VARCHAR(40)," \
											"mete_num INT1,device_kind INT1," \
											"device_type INT2, online INT1," \
											"createTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"UpdateTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime')));"
/**********************************************************************************************************************/
#define IOT_CFG_ACTION_TB_CREATE_SQL		"CREATE TABLE IF NOT EXISTS "IOT_CFG_ACTION_TB" " \
											"(action_id INTEGER PRIMARY KEY," \
											"deviceId VARCHAR(16)," \
											"meteId VARCHAR(14)," \
											"scenarioId INT,ruleId INT," \
											"vaule INT," \
											"createTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"UpdateTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"sub_ruleId INT);"
/**********************************************************************************************************************/
#define IOT_CFG_AUTO_TB_CREATE_SQL			"CREATE TABLE IF NOT EXISTS "IOT_CFG_AUTO_TB" " \
											"(rule_id INTEGER PRIMARY KEY," \
											"delay INT," \
											"type INT1," \
											"priority INT1," \
											"status INT1," \
											"start_time INT," \
											"end_time INT," \
											"week INT1," \
											"createTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"UpdateTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime')));"
/**********************************************************************************************************************/
#define IOT_CFG_TRIGGER_TB_CREATE_SQL		"CREATE TABLE IF NOT EXISTS "IOT_CFG_TRIGGER_TB" " \
											"(triggerId INTEGER PRIMARY KEY," \
											"rule_id INT REFERENCES iot_cfg_auto(rule_id) ON UPDATE CASCADE," \
											"relation_type INT1," \
											"device_id VARCHAR(16)," \
											"datetimer INT," \
											"week INT1," \
											"mete_id VARCHAR(14)," \
											"operator VARCHAR(8)," \
											"right_value INT," \
											"createTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"UpdateTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime')));"
/**********************************************************************************************************************/
#define IOT_BAS_ALMINFOEXT_TB_CREATE_SQL	"CREATE TABLE IF NOT EXISTS "IOT_BAS_ALMINFOEXT_TB" " \
											"(device_type INT2," \
											"device_model INT2," \
											"mete_type INT2," \
											"report_level INT1," \
											"upperlimit1_exist INT1," \
											"upperlimit1 REAL," \
											"lowerlimit1_exist INT1," \
											"lowerlimit1 REAL," \
											"upperlimit2_exist INT1," \
											"upperlimit2 REAL," \
											"lowerlimit2_exist INT1," \
											"lowerlimit2 REAL," \
											"upperlimit3_exist INT1," \
											"upperlimit3 REAL," \
											"lowerlimit3_exist INT1," \
											"lowerlimit3 REAL," \
											"upperlimit4_exist INT1," \
											"upperlimit4 REAL," \
											"lowerlimit4_exist INT1," \
											"lowerlimit4 REAL," \
											"delayAlarm_time INT," \
											"delayCancelAlarm_time INT," \
											"delta REAL," \
											"PRIMARY KEY(device_type,mete_type));"
/**********************************************************************************************************************/
#define IOT_HIS_DEVICEALARM_TB_CREATE_SQL	"CREATE TABLE IF NOT EXISTS "IOT_HIS_DEVICEALARM_TB" " \
											"(alarm_no INT," \
											"device_sn VARCHAR(17)," \
											"bas_mete_id VARCHAR(15)," \
											"mete_kind INT1," \
											"report_level INT1," \
											"device_type INT2," \
											"mete_type INT2," \
											"alarm_time INT," \
											"alarm_value REAL," \
											"ack INT1," \
											"clear_time INT," \
											"clear_value REAL," \
											"status INT1," \
											"sqno INT," \
											"bas_channel_no INT1," \
											"operate_time TimeStamp NOT NULL DEFAULT (datetime('now','localtime'))," \
											"PRIMARY KEY(alarm_no));"
/**********************************************************************************************************************/


#endif
#endif
