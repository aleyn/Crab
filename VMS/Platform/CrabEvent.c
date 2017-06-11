/******************** Copyright wisearm.com *********************************
* File Name         : CrabEvent.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 事件管理器
********************************************************************************/
#include "CrabVMS.h"
#include "CrabEvent.h"

__cache GapByte  ControlBuffer[CONTROL_SIZE];
__cache TGapData ControlRX;

extern uint16_t BoardKey;
extern uint16_t RemoteKey;

/*******************************************************************************
 * Function    : CrabEventTask
 * Caption     : 事件任务
 * Description : .
 *******************************************************************************/
void CrabEventTask()
{ 
  CrabUint    Key;
  CrabInt     Count;
  TGap        Gap;
  
  CrabTaskSuspend(CRAB_TASK_EVENT);
  GapInit(&Gap, ControlBuffer, CONTROL_SIZE);  
  
  while (1)
  {
  #if KEY_BUFFER_MODE == 1
    CrabHW_KEY_Scan();
    Key = CrabHW_KEY_Read();
  #else
    Key = CrabHW_KEY_Scan();
  #endif
    if (Key)
    {
      BoardKey = Key;
    #if KEY_DETAIL == 1
      CrabFifo_PushEvent(KEY_PRESS | Key);
    #else
      CrabFifo_PushEvent(KEY_PRESS);
    #endif
    }
    
    if (nRF24_IRQ_Active())
    {
      //GPIO_SetBit(USER_LED, LED_ON);
      Count = nRF24_ReadReg(nRF24_CMD_R_RX_PL_WID);
      
      if ((Count) && (nRF24_RXPacket(ControlBuffer, Count)))
      {
        if (GapDecodeBuffer(&Gap, &ControlRX, sizeof(TGapData)) == GAP_Success)
        {
          if ((ControlRX.Command == GAP_CMD_CONTROL) && (ControlRX.Control.Port == 1) && (ControlRX.Size > GAP_MINISIZE_CONTROL))
          {
            Key = ControlRX.Control.bValue[0];
            
            if (Key)
            {
              //CrabVMS_log("Remote Control : %2.2x", Key);
              
              RemoteKey = Key;
            #if CONTROL_DETAIL == 1
              CrabFifo_PushEvent(REMOTE_CONTROL | Key);
            #else
              CrabFifo_PushEvent(REMOTE_CONTROL);
            #endif
            }
          }
        }
      }
      
      nRF24_FlashFifo(1, 1);
    }    
    
    CrabDelay(10);
  }
}
  


// END OF FILE