/******************** Copyright wisearm.com *********************************
* File Name         : CrabBoardApi.c
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API for MICO
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabApiTimerConfig    ();
crabapi CrabApiBeep           ();
crabapi CrabApiWriteCOM       ();

/*******************************************************************************
* Function    : CrabRegisterFuncApi
* Caption     : ×¢²á°åÔØAPIº¯Êı 
* Description : .
*******************************************************************************/
void CrabRegisterFuncApi()
{  
  CrabExtern_RegisterApi("TimerConfig", CrabApiTimerConfig);
  CrabExtern_RegisterApi("Beep", CrabApiBeep);
  CrabExtern_RegisterApi("WriteCOM", CrabApiWriteCOM);
}

/*******************************************************************************
* Function    : CrabApiTimerConfig
* Caption     : ÅäÖÃÓ²¼şTIMER
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiTimerConfig ()
{
  uint8_t TIM;
  uint32_t Period;
  uint32_t Prescaler;
    
  if (!CrabExtern_PopupParamAsByte(TIM)) return;
  if (!CrabExtern_PopupParamAsUint(Period)) return;
  if (!CrabExtern_PopupParamAsUint(Prescaler)) return;
  
  
  CrabHW_TIM_Config(TIM, Period, Prescaler);
}

/*******************************************************************************
* Function    : CrabApiBeep
* Caption     : ·äÃùÆ÷·¢Éù
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiBeep ()
{
  uint8_t Width;
  uint8_t Count;
    
  if (!CrabExtern_PopupParamAsByte(Width)) return;
  if (!CrabExtern_PopupParamAsByte(Count)) return;

  CrabChangeBeep(Width / CRAB_SYSTEM_TICK, Count);
}

/*******************************************************************************
* Function    : CrabApiWriteCOM
* Caption     : ·¢ËÍ×Ö·û´®µ½´®¿Ú
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiWriteCOM ()
{
  CrabString ComStr; 
  
  if (!CrabExtern_PopupParamAsString(ComStr)) return;  
  if (ComStr == null) return;

  printf(ComStr->Data);
}
