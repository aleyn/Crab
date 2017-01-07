/******************** Copyright wisearm.com *********************************
* File Name         : CrabBoardApi.c
* Author            : Œ‚¥¥√˜(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API for MICO
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabApiTimerConfig    ();
crabapi CrabApiBeep           ();
crabapi CrabApiWriteCOM       ();
crabapi CrabApiNetInfo        ();

/*******************************************************************************
* Function    : CrabRegisterFuncApi
* Caption     : ◊¢≤·∞Â‘ÿAPI∫Ø ˝ 
* Description : .
*******************************************************************************/
void CrabRegisterFuncApi()
{  
  CrabExtern_RegisterApi("TimerConfig", CrabApiTimerConfig);
  CrabExtern_RegisterApi("Beep", CrabApiBeep);
  CrabExtern_RegisterApi("WriteCOM", CrabApiWriteCOM);
  CrabExtern_RegisterApi("NetInfo", CrabApiNetInfo);
}

/*******************************************************************************
* Function    : CrabApiTimerConfig
* Caption     : ≈‰÷√”≤º˛TIMER
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiTimerConfig ()
{
  uint8_t TIM;
  uint32_t Period;
  uint32_t Prescaler;
  
  TIM = CrabExtern_GetUintParam(1); 
  Period = CrabExtern_GetUintParam(2);
  Prescaler = CrabExtern_GetUintParam(3);    
  CrabHW_TIM_Config(TIM, Period, Prescaler);
}

/*******************************************************************************
* Function    : CrabApiBeep
* Caption     : ∑‰√˘∆˜∑¢…˘
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiBeep ()
{
  uint8_t Width;
  uint8_t Count;
  
  Width = CrabExtern_GetUintParam(1);  
  Count = CrabExtern_GetUintParam(2);
  
  CrabChangeBeep(Width, Count);
}

/*******************************************************************************
* Function    : CrabApiWriteCOM
* Caption     : ∑¢ÀÕ◊÷∑˚¥ÆµΩ¥Æø⁄
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiWriteCOM ()
{
  CrabStringCreate(CmdStr, 255);
  CrabExtern_ConvertParamToString(1, CmdStr);
  printf(CmdStr->Data);
}

/*******************************************************************************
* Function    : CrabApiNetInfo
* Caption     : œ‘ æÕ¯¬Á–≈œ¢
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiNetInfo ()
{  
  //Log("CONFIG  Reg[%.2X] = %.2X;", 0x00, nRF24_ReadReg(0x00));
  //Log("STATUS  Reg[%.2X] = %.2X;", 0x07, nRF24_ReadReg(0x07));
  //Log("OBSERVE Reg[%.2X] = %.2X;", 0x08, nRF24_ReadReg(0x08));
  //Log("FIFO    Reg[%.2X] = %.2X;", 0x17, nRF24_ReadReg(0x17));
  //Log("CHANNEL Reg[%.2X] = %d;", 5, nRF24_ReadReg(5));  
}
