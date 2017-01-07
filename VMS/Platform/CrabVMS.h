/******************** Copyright wisearm.com *********************************
* File Name         : CrabVMS.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 配置文件
********************************************************************************/

#ifndef __CRAB_VMS_MANAGE__
#define __CRAB_VMS_MANAGE__

#include "CrabHardware.h"
#include "CrabConfig.h"
#include "CrabBaseType.h"
#include "CrabErrorMsg.h"
#include "CrabString.h"
#include "CrabStream.h"
#include "CrabStoreStream.h"
#include "CrabStorage.h"
#include "CrabExecute.h"
#include "CrabExtern.h"
#include "CrabDefaultApi.h"
#include "CrabDatetime.h"
#include "CrabFifo.h"
#include "CrabPlatform.h"

#ifdef  __cplusplus
extern "C" {
#endif
  
//版本信息
#define CRAB_DEVICE_ID            101
#define CRAB_VENDER_ID            2282902
#define CRAB_HW_VER               0x0101
    
#define CRAB_LED_OFF              0x00
#define CRAB_LED_GREEN_ON         0x01
#define CRAB_LED_RED_ON           0x02
#define CRAB_LED_GREEN_FLASH      0x11
#define CRAB_LED_RED_FLASH        0x12
#define CRAB_LED_GREEN_ERROR      0x21
#define CRAB_LED_RED_ERROR        0x22
  
#define CRAB_BEEP_STOP            0x00
#define CRAB_BEEP_START           0x01
  
#define CRAB_TASK_SYSTEM          0x01
#define CRAB_TASK_COMMAND         0x02
#define CRAB_TASK_APPLICATION     0x03
#define CRAB_TASK_EVENT           0x04

//运行虚拟机
void CrabSystem_Running();

//创建任务
void CrabCreateTask(CrabByte TaskID);

//休眠任务
void CrabTaskSuspend(CrabByte TaskID);
void CrabTaskSuspendFromISR(CrabByte TaskID);

//唤醒任务
void CrabTaskResume(CrabByte TaskID);
void CrabTaskResumeFromISR(CrabByte TaskID);

//系统级任务
void CrabSystemTask();

//通讯命令任务
void CrabCommandTask();

//事件任务
void CrabEventTask();

//应用任务
void CrabApplicationTask();

//注册静态API函数
void CrabRegisterStaticApi(); 

//注册时钟API函数
void CrabRegisterClockApi(); 

//注册轻端口API函数
void CrabRegisterPortApi();

//注册板载API函数
void CrabRegisterFuncApi();

//更改虚拟机运行状态
void CrabChangeAppState(CrabByte State);

//更改系统LED灯状态
void CrabChangeLEDStatus(CrabByte Status);

//更新声音状态
void CrabChangeBeep(CrabByte Width, CrabByte Count);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE