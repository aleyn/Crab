/******************** Copyright wisearm.com *********************************
* File Name         : CrabUtility.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 其它工具
********************************************************************************/
#include "CrabVMS.h"
#include "CrabUtility.h"
/*******************************************************************************
* Function    : fputc
* Caption     : 支援Printf的函数
*  @Param     : 1.ch - 
*  @Param     : 2.f - 
* Return      : int
* Description : .
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(PRINTF_COM, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(PRINTF_COM, USART_FLAG_TC) == RESET);

  return ch;
}
/** @} */
