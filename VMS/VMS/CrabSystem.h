/******************** Copyright wisearm.com *********************************
* File Name         : CrabSystem.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 系统进程管理文件
********************************************************************************/

#ifndef __CRAB_SYSTEM_MANAGE__
#define __CRAB_SYSTEM_MANAGE__

#include "CrabBaseType.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* 50ms base
#define CRAB_SYSTEM_TICK          50
#define CRAB_SYSTEM_LED_ERROR     2
#define CRAB_SYSTEM_LED_FLASH     10
#define CRAB_SYSTEM_KEY_LONG      200
#define CRAB_SYSTEM_KEY_SHORT     20
#define CRAB_SYSTEM_ALARM_TICK    5
*/

// 10ms base
#define CRAB_SYSTEM_TICK          10
#define CRAB_SYSTEM_LED_ERROR     10
#define CRAB_SYSTEM_LED_FLASH     50
#define CRAB_SYSTEM_KEY_LONG      300
#define CRAB_SYSTEM_KEY_SHORT     30
#define CRAB_SYSTEM_ALARM_TICK    5

  
#define CRAB_LED_OFF              0x00
#define CRAB_LED_GREEN_ON         0x01
#define CRAB_LED_RED_ON           0x02
#define CRAB_LED_GREEN_FLASH      0x11
#define CRAB_LED_RED_FLASH        0x12
#define CRAB_LED_GREEN_ERROR      0x21
#define CRAB_LED_RED_ERROR        0x22
  
#define CRAB_BEEP_STOP            0x00
#define CRAB_BEEP_START           0x01

#define CRAB_SECOND_EVENT         0x80000000
  
#define CRAB_ALARM_EVENT          0x81000000
#define CRAB_ALARM_COUNT          10
#define CRAB_ALARM_SEC_CHECK      (1000 / CRAB_SYSTEM_TICK / CRAB_SYSTEM_ALARM_TICK)
#define CRAB_ALARM_HOUR_CHECK     (3600 * CRAB_ALARM_SEC_CHECK)
#define CRAB_ALARM_MSECOFDAY      86400000
  
#define CRAB_ALARM_STOP           0x00
#define CRAB_ALARM_ONCE           0x80
#define CRAB_ALARM_LOOP           0xFF
  
#define CRAB_ALARM_TIME           0x01
#define CRAB_ALARM_WEEK           0x02
#define CRAB_ALARM_DAY            0x03
#define CRAB_ALARM_DATE           0x04
  
#pragma pack(1)
typedef struct
{
  CrabByte  Active;
  CrabByte  AlarmType;
  CrabUint  NextCheck;
  TCrabDate Date;
  CrabTime  Time;
} TCrabAlarmClock, *PCrabAlarmClock, CrabAlarmClock;
#pragma pack()

//运行虚拟机
void CrabSystem_Running();
 
//系统级任务
void CrabSystemTask();

//更改系统LED灯状态
void CrabUpdateLEDStatus();

//更新声音状态
void CrabChangeBeep(CrabShort Width, CrabByte Count);

//设置闹钟
void CrabAlarmSetup(CrabByte Index, PCrabAlarmClock AlarmClockInfo);

//关闭闹钟
void CrabAlarmClose(CrabByte Index);
void CrabAlarmCloseAll();

//秒信号事件
void CrabAlarmSecondEvent();

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE