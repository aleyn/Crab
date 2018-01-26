/******************** Copyright wisearm.com *********************************
* File Name         : CrabBoardApi.c
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : API for MICO
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabApiBeep           ();
crabapi CrabApiWriteCOM       ();

crabapi CrabApiMyAPIFunc      ();
/*******************************************************************************
* Function    : CrabRegisterFuncApi
* Caption     : ×¢²á°åÔØAPIº¯Êý 
* Description : .
*******************************************************************************/
void CrabRegisterFuncApi()
{  
  CrabExtern_RegisterApi("Beep", CrabApiBeep);
  CrabExtern_RegisterApi("WriteCOM", CrabApiWriteCOM);
  
  CrabExtern_RegisterApi("MyAPIFunc", CrabApiMyAPIFunc);    
}

/*******************************************************************************
* Function    : CrabApiBeep
* Caption     : ·äÃùÆ÷·¢Éù
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiBeep ()
{
  CrabUShort Width;
  CrabByte Count;
    
  if (!CrabExtern_PopupParamAsUShort(Width)) return;
  if (!CrabExtern_PopupParamAsByte(Count)) return;

  CrabChangeBeep(Width, Count);
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

/*******************************************************************************
* Function    : CrabApiMyAPIFunc
* Caption     : APIº¯ÊýÑÝÊ¾
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiMyAPIFunc ()
{
  CrabInt       Result = 0;
  CrabInt       Param1;
  CrabInt       Param2;

  do
  {
    if (!CrabExtern_PopupParamAsInt(Param1)) break;
    if (!CrabExtern_PopupParamAsInt(Param2)) break;

    Result = Param1 + Param2;
  } while (0);
  
  CrabExtern_ReturnValueAsInt(Result);
}