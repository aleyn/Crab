/******************** Copyright wisearm.com *********************************
* File Name         : CrabTask.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : ���������
********************************************************************************/

#include "CrabVMS.h"
#include "CrabTask.h"

xSemaphoreHandle  CrabSemaphoreMutex[CRAB_TASK_MUTEX_COUNT] = {NULL};

#define           CrabSystem_Task_Name            (TASK_NAME)"CrabSystem"
#define           CrabSystem_Task_Level           TASK_PRIO(3)
#define           CrabSystem_Task_Size            384
#define           CrabSystem_Task_Param           NULL
TASK_HANDLE 	    CrabSystem_Task_Object;

#define           CrabCommand_Task_Name           (TASK_NAME)"CrabCommand"
#define           CrabCommand_Task_Level          TASK_PRIO(6)
#define           CrabCommand_Task_Size           256
#define           CrabCommand_Task_Param          NULL
TASK_HANDLE 	    CrabCommand_Task_Object;

#define           CrabDebug_Task_Name             (TASK_NAME)"CrabDebug"
#define           CrabDebug_Task_Level            TASK_PRIO(6)
#define           CrabDebug_Task_Size             256
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
* Caption     : ��������
*  @Param     : 1.TaskID - ����ID��
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
#ifdef  CRABVMS_DEBUG
      xTaskCreate(CrabDebug_Task,
                  CrabDebug_Task_Name,
                  CrabDebug_Task_Size,
                  CrabDebug_Task_Param,
                  CrabDebug_Task_Level,
                 &CrabDebug_Task_Object);
#endif
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
* Caption     : ��������
*  @Param     : 1.TaskID - ����ID��
* Description : ������������ʹ��
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
#ifdef  CRABVMS_DEBUG
      vTaskSuspend(CrabDebug_Task_Object);
#endif
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
* Caption     : ��������
*  @Param     : 1.TaskID - ����ID��
* Description : ��Ӳ���жϺ�����ʹ��
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
#ifdef  CRABVMS_DEBUG
      vTaskSuspend(CrabDebug_Task_Object);
#endif
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
* Caption     : ��������
*  @Param     : 1.TaskID - ����ID��
* Description : ������������ʹ��
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
#ifdef  CRABVMS_DEBUG
      vTaskResume(CrabDebug_Task_Object);
#endif
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
* Caption     : ��������
*  @Param     : 1.TaskID - ����ID��
* Description : ��Ӳ���жϺ�����ʹ��
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
#ifdef  CRABVMS_DEBUG
      xTaskResumeFromISR(CrabDebug_Task_Object);
#endif
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

/*******************************************************************************
* Function    : CrabTaskMutexInit
* Caption     : ���������ź�
* Description : 
*******************************************************************************/
void CrabTaskMutexInit()
{
  CrabByte Index;
  
  for (Index = 0; Index < CRAB_TASK_MUTEX_COUNT; Index ++)
  {
    CrabSemaphoreMutex[Index] = xSemaphoreCreateMutex();
  }
}

/*******************************************************************************
* Function    : CrabTaskMutexEnter
* Caption     : ���뻥��
*  @Param     : 1.Index - �����ź�����
* Description : 
*******************************************************************************/
CrabBool CrabTaskMutexEnter(CrabByte Index)
{
  if (CrabSemaphoreMutex[Index] == NULL)
  {
    CrabSemaphoreMutex[Index] = xSemaphoreCreateMutex();
  }
  
  return xSemaphoreTake(CrabSemaphoreMutex[Index], 0); 
}

/*******************************************************************************
* Function    : CrabTaskMutexEnterISR
* Caption     : ���뻥���жϷ�ʽ
*  @Param     : 1.Index - �����ź�����
* Description : 
*******************************************************************************/
CrabBool CrabTaskMutexEnterISR(CrabByte Index)
{
  if (CrabSemaphoreMutex[Index] == NULL)
  {
    CrabSemaphoreMutex[Index] = xSemaphoreCreateMutex();
  }
  
  return xSemaphoreTakeFromISR(CrabSemaphoreMutex[Index], 0); 
}

/*******************************************************************************
* Function    : CrabTaskMutexExit
* Caption     : �뿪����
*  @Param     : 1.Index - �����ź�����
* Description : 
*******************************************************************************/
CrabBool CrabTaskMutexExit(CrabByte Index)
{
  if (CrabSemaphoreMutex[Index] == NULL)
  {
    return CrabFalse;
  }
  
  return xSemaphoreGive(CrabSemaphoreMutex[Index]); 
}

/*******************************************************************************
* Function    : CrabTaskMutexExitISR
* Caption     : �뿪�����жϷ�ʽ
*  @Param     : 1.Index - �����ź�����
* Description : 
*******************************************************************************/
CrabBool CrabTaskMutexExitISR(CrabByte Index)
{
  static BaseType_t xHigherPriorityTaskWoken;
  CrabBool Result;

  if (CrabSemaphoreMutex[Index] == NULL)
  {
    return CrabFalse;
  }
  
  Result = xSemaphoreGiveFromISR(CrabSemaphoreMutex[Index], &xHigherPriorityTaskWoken); 
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  
  return Result;
}
// END OF FILE