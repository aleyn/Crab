/******************** Copyright wisearm.com *********************************
* File Name         : CrabTASK.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 任务管理器
********************************************************************************/

#ifndef __CRAB_TASK_MANAGE__
#define __CRAB_TASK_MANAGE__

#include "CrabBaseType.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#ifdef  __cplusplus
extern "C" {
#endif
  
#define CRAB_TASK_SYSTEM          0x01
#define CRAB_TASK_COMMAND         0x02
#define CRAB_TASK_APPLICATION     0x03
#define CRAB_TASK_DEBUG           0x04
#define CRAB_TASK_EVENT           0x05
  
#define RTOS_HIGHEST_PRIORITY     9
#define TASK_HANDLE               static xTaskHandle
#define TASK_NAME                 char const*
#define TASK_PRIO(P)              (RTOS_HIGHEST_PRIORITY - P)  

//互斥信号量
#define CRAB_TASK_MUTEX_COUNT     3
#define CRAB_TASK_MUTEX_DEFAULT   0
#define CRAB_TASK_MUTEX_ALARM     1
#define CRAB_TASK_MUTEX_EVENT     2
  
//创建任务
void CrabCreateTask(CrabByte TaskID);

//休眠任务
void CrabTaskSuspend(CrabByte TaskID);
void CrabTaskSuspendFromISR(CrabByte TaskID);

//唤醒任务
void CrabTaskResume(CrabByte TaskID);
void CrabTaskResumeFromISR(CrabByte TaskID);

//建立互斥信号
void CrabTaskMutexInit();
//进入互斥
CrabBool CrabTaskMutexEnter(CrabByte Index);
//进入互斥，中断方式
CrabBool CrabTaskMutexEnterISR(CrabByte Index);
//离开互斥
CrabBool CrabTaskMutexExit(CrabByte Index);
//离开互斥，中断方式
CrabBool CrabTaskMutexExitISR(CrabByte Index);

#ifdef  __cplusplus
}
#endif
#endif   // END OF FILE