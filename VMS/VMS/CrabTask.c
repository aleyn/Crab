/******************** Copyright wisearm.com *********************************
* File Name         : CrabTask.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 任务管理器
********************************************************************************/

#include "CrabVMS.h"
#include "CrabTask.h"

//uint32_t   TickCount = 0;

#define           CrabSystem_Task_Name            (TASK_NAME)"CrabSystem"
#define           CrabSystem_Task_Level           TASK_PRIO(3)
#define           CrabSystem_Task_Size            128
#define           CrabSystem_Task_Param           NULL
TASK_HANDLE 	    CrabSystem_Task_Object;

#define           CrabCommand_Task_Name           (TASK_NAME)"CrabCommand"
#define           CrabCommand_Task_Level          TASK_PRIO(6)
#define           CrabCommand_Task_Size           256
#define           CrabCommand_Task_Param           NULL
TASK_HANDLE 	    CrabCommand_Task_Object;

#define           CrabDebug_Task_Name             (TASK_NAME)"CrabDebug"
#define           CrabDebug_Task_Level            TASK_PRIO(7)
#define           CrabDebug_Task_Size             128
#define           CrabDebug_Task_Param            NULL
TASK_HANDLE 	    CrabDebug_Task_Object;

#define           CrabEvent_Task_Name             (TASK_NAME)"CrabEvent"
#define           CrabEvent_Task_Level            TASK_PRIO(7)
#define           CrabEvent_Task_Size             256
#define           CrabEvent_Task_Param            NULL
TASK_HANDLE 	    CrabEvent_Task_Object;

#define           CrabApplication_Task_Name       (TASK_NAME)"CrabApplication"
#define           CrabApplication_Task_Level      TASK_PRIO(8)
#define           CrabApplication_Task_Size       512
#define           CrabApplication_Task_Param      NULL
TASK_HANDLE 	    CrabApplication_Task_Object;

/*******************************************************************************
* Function    : CrabSystem_Task
* Caption     : .
*  @Param     : 1.parg - 
* Description : .
*******************************************************************************/
void CrabSystem_Task(void *parg)
{
  CrabSystemTask();
  vTaskDelete( NULL );
}

/*******************************************************************************
* Function    : CrabCommand_Task
* Caption     : .
*  @Param     : 1.parg - 
* Description : .
*******************************************************************************/
void CrabCommand_Task(void *parg)
{
  CrabCommandTask();
  vTaskDelete( NULL );
}

/*******************************************************************************
* Function    : CrabDebug_Task
* Caption     : .
*  @Param     : 1.parg - 
* Description : .
*******************************************************************************/
void CrabDebug_Task(void *parg)
{
  CrabUserDebugTask();
  vTaskDelete( NULL );
}

/*******************************************************************************
* Function    : CrabEvent_Task
* Caption     : .
*  @Param     : 1.parg - 
* Description : .
*******************************************************************************/
void CrabEvent_Task(void *parg)
{
  CrabEventTask();
  vTaskDelete( NULL );
}

/*******************************************************************************
* Function    : CrabApplication_Task
* Caption     : .
*  @Param     : 1.parg - 
* Description : .
*******************************************************************************/
void CrabApplication_Task(void *parg)
{
  CrabApplicationTask();
  vTaskDelete( NULL );
}

/*******************************************************************************
* Function    : CrabCreateTask
* Caption     : 创建任务
*  @Param     : 1.TaskID - 任务ID号
* Description : .
*******************************************************************************/
void CrabCreateTask(CrabByte TaskID)
{    
  switch (TaskID)
  {
    case CRAB_TASK_SYSTEM:
    {
      xTaskCreate(CrabSystem_Task,
                  CrabSystem_Task_Name,
                  CrabSystem_Task_Size,
                  CrabSystem_Task_Param,
                  CrabSystem_Task_Level,
                 &CrabSystem_Task_Object);
      
      break;
    }
    case CRAB_TASK_COMMAND:
    {
      xTaskCreate(CrabCommand_Task,
                  CrabCommand_Task_Name,
                  CrabCommand_Task_Size,
                  CrabCommand_Task_Param,
                  CrabCommand_Task_Level,
                 &CrabCommand_Task_Object);
      
      break;
    }
    case CRAB_TASK_DEBUG:
    {
      xTaskCreate(CrabDebug_Task,
                  CrabDebug_Task_Name,
                  CrabDebug_Task_Size,
                  CrabDebug_Task_Param,
                  CrabDebug_Task_Level,
                 &CrabDebug_Task_Object);
      
      break;
    }
    case CRAB_TASK_EVENT:
    {
      xTaskCreate(CrabEvent_Task,
                  CrabEvent_Task_Name,
                  CrabEvent_Task_Size,
                  CrabEvent_Task_Param,
                  CrabEvent_Task_Level,
                 &CrabEvent_Task_Object);
      
      break;
    }
    case CRAB_TASK_APPLICATION:
    {
      xTaskCreate(CrabApplication_Task,
                  CrabApplication_Task_Name,
                  CrabApplication_Task_Size,
                  CrabApplication_Task_Param,
                  CrabApplication_Task_Level,
                 &CrabApplication_Task_Object);  
      
      break;
    }
  }  
}

/*******************************************************************************
* Function    : CrabTaskSuspend
* Caption     : 休眠任务
*  @Param     : 1.TaskID - 任务ID号
* Description : 在其它任务中使用
*******************************************************************************/
void CrabTaskSuspend(CrabByte TaskID)
{
  switch (TaskID)
  {
    case CRAB_TASK_SYSTEM:
    {
      vTaskSuspend(CrabSystem_Task_Object);
      break;
    }
    case CRAB_TASK_COMMAND:
    {
      vTaskSuspend(CrabCommand_Task_Object);
      break;
    }
    case CRAB_TASK_DEBUG:
    {
      vTaskSuspend(CrabDebug_Task_Object);
      break;
    }
    case CRAB_TASK_EVENT:
    {
      vTaskSuspend(CrabEvent_Task_Object);
      break;
    }
    case CRAB_TASK_APPLICATION:
    {
      vTaskSuspend(CrabApplication_Task_Object);
      break;
    }
  }
}

/*******************************************************************************
* Function    : CrabTaskSuspendFromISR
* Caption     : 休眠任务
*  @Param     : 1.TaskID - 任务ID号
* Description : 在硬件中断函数中使用
*******************************************************************************/
void CrabTaskSuspendFromISR(CrabByte TaskID)
{
  switch (TaskID)
  {
    case CRAB_TASK_SYSTEM:
    {
      vTaskSuspend(CrabSystem_Task_Object);
      break;
    }
    case CRAB_TASK_COMMAND:
    {
      vTaskSuspend(CrabCommand_Task_Object);
      break;
    }
    case CRAB_TASK_DEBUG:
    {
      vTaskSuspend(CrabDebug_Task_Object);
      break;
    }
    case CRAB_TASK_EVENT:
    {
      vTaskSuspend(CrabEvent_Task_Object);
      break;
    }
    case CRAB_TASK_APPLICATION:
    {
      vTaskSuspend(CrabApplication_Task_Object);
      break;
    }
  }
}

/*******************************************************************************
* Function    : CrabTaskResume
* Caption     : 唤醒任务
*  @Param     : 1.TaskID - 任务ID号
* Description : 在其它任务中使用
*******************************************************************************/
void CrabTaskResume(CrabByte TaskID)
{
  switch (TaskID)
  {
    case CRAB_TASK_SYSTEM:
    {
      vTaskResume(CrabSystem_Task_Object);
      break;
    }
    case CRAB_TASK_COMMAND:
    {
      vTaskResume(CrabCommand_Task_Object);
      break;
    }
    case CRAB_TASK_DEBUG:
    {
      vTaskResume(CrabDebug_Task_Object);
      break;
    }
    case CRAB_TASK_EVENT:
    {
      vTaskResume(CrabEvent_Task_Object);
      break;
    }
    case CRAB_TASK_APPLICATION:
    {
      vTaskResume(CrabApplication_Task_Object);
      break;
    }
  }
}

/*******************************************************************************
* Function    : CrabTaskResumeFromISR
* Caption     : 唤醒任务
*  @Param     : 1.TaskID - 任务ID号
* Description : 在硬件中断函数中使用
*******************************************************************************/
void CrabTaskResumeFromISR(CrabByte TaskID)
{
  switch (TaskID)
  {
    case CRAB_TASK_SYSTEM:
    {
      xTaskResumeFromISR(CrabSystem_Task_Object);
      break;
    }
    case CRAB_TASK_COMMAND:
    {
      xTaskResumeFromISR(CrabCommand_Task_Object);
      break;
    }
    case CRAB_TASK_DEBUG:
    {
      xTaskResumeFromISR(CrabDebug_Task_Object);
      break;
    }
    case CRAB_TASK_EVENT:
    {
      xTaskResumeFromISR(CrabEvent_Task_Object);
      break;
    }
    case CRAB_TASK_APPLICATION:
    {
      xTaskResumeFromISR(CrabApplication_Task_Object);
      break;
    }
  }
}


// END OF FILE