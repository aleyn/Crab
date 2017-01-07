/******************** Copyright wisearm.com *********************************
* File Name         : CrabEvent.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 通讯管理器
********************************************************************************/
#include "CrabVMS.h"

#define KEY_PRESS  0x01000000

/*******************************************************************************
 * Function    : CrabEventTask
 * Caption     : 事件任务
 * Description : .
 *******************************************************************************/
void CrabEventTask()
{ 
  CrabUint Key;
  
  CrabTaskSuspend(CRAB_TASK_EVENT);
  
  while (1)
  {
    Key = CrabHW_KEY_Scan();
    
    if (Key)
    {
      CrabFifo_PushEvent(KEY_PRESS | Key);
    }
    
    CrabDelay(10);
  }
}

// END OF FILE