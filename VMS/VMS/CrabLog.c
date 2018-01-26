/******************** Copyright wisearm.com *********************************
* File Name         : CrabLog.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-08-19
* Description       : 日志方式
********************************************************************************/
#include "CrabVMS.h"
#include "CrabLog.h"
#include "CrabLogo.h"
#include <stdio.h>
#include <stdarg.h>

CrabChar LogBuffer[255];

/*******************************************************************************
 * Function    : Log
 * Caption     : 日志
 * Description : .
 *******************************************************************************/
void Log(char* Title, char* fmt, ...)
{
  uint32_t Length, Length2;
      
  //if (mico_debug_enabled==0) return;  
  //mico_rtos_lock_mutex( &stdio_tx_mutex );

  va_list argPt;
  va_start(argPt, fmt);
  
  Length = vsnprintf(LogBuffer, 255, fmt, argPt);
  LogBuffer[Length++] = 0x0D;
  LogBuffer[Length++] = 0x0A;
  LogBuffer[Length] = 0;
  
  Length2 = strlen(Title);
  
  //串口方式   
  if ((Title != null) && (Length2))
  {
    CrabHW_PutString(Title, Length2);
  }
  
  if (Length)
  {
    CrabHW_PutString(LogBuffer, Length);
  }  
  
  //USBGAP方式
  /*
  if USB_LogCheck(&Buf, Length)
  {
    CrabMemCopy(Buf, Text, Length);
    USB_LogAdd(0, Length);
  }
  */   
  
  //mico_rtos_unlock_mutex( &stdio_tx_mutex );
}

/*******************************************************************************
 * Function    : ShowLogo
 * Caption     : 显示LOGO
 * Description : .
 *******************************************************************************/
void ShowLogo()
{
  printf("\r\n");
  printf(CRAB_LOGO_1);
  printf(CRAB_LOGO_2);
  printf(CRAB_LOGO_3);
  printf(CRAB_LOGO_4);
  printf(CRAB_LOGO_5);
  printf(CRAB_LOGO_6);
  printf(CRAB_LOGO_7);
  printf(CRAB_LOGO_8);
  printf("\r\n");  
}
// END OF FILE