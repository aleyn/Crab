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
    
#define CRAB_SYSTEM_TICK          50
  
#define CRAB_LED_OFF              0x00
#define CRAB_LED_GREEN_ON         0x01
#define CRAB_LED_RED_ON           0x02
#define CRAB_LED_GREEN_FLASH      0x11
#define CRAB_LED_RED_FLASH        0x12
#define CRAB_LED_GREEN_ERROR      0x21
#define CRAB_LED_RED_ERROR        0x22
  
#define CRAB_BEEP_STOP            0x00
#define CRAB_BEEP_START           0x01

//运行虚拟机
void CrabSystem_Running();
 
//系统级任务
void CrabSystemTask();

//更改系统LED灯状态
void CrabChangeLEDStatus(CrabByte Status);

//更新声音状态
void CrabChangeBeep(CrabByte Width, CrabByte Count);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE