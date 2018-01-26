/******************** Copyright wisearm.com *********************************
* File Name         : CrabUserDebug.c
* Author            : �ⴴ��(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : �û��Զ���Ӳ����������
********************************************************************************/
#include "CrabVMS.h"
#include "CrabUserDebug.h"

/*******************************************************************************
 * Function    : CrabEventTask
 * Caption     : �¼�����
 * Description : .
 *******************************************************************************/
void CrabUserDebugTask()
{  
  CrabTaskSuspend(CRAB_TASK_DEBUG);
  
  while (1)
  {
    CrabVMS_Log("Running in DEBUG mode...");
    
    CrabUserDebug( );
    
    CrabTaskSuspend(CRAB_TASK_DEBUG);
  }
}

void CrabUserDebug()
{
  uint8_t pcWriteBuffer[500];
  vTaskList((char *)pcWriteBuffer);
  printf("TaskName       Status Level Stack Index\r\n");
  printf("%s\r\n", pcWriteBuffer);
}



// END OF FILE