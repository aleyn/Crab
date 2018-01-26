/******************** Copyright wisearm.com *********************************
* File Name         : CrabLCD.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-09-21
* Description       : API for LCD Display
********************************************************************************/
#include "CrabVMS.h"

crabapi CrabApiLcdClear       ();
crabapi CrabApiLcdClearLine   ();
crabapi CrabApiLcdSetCursor   ();
crabapi CrabApiLcdSetScreen   ();
crabapi CrabApiLcdSetLight   ();
crabapi CrabApiLcdDisplay     ();
crabapi CrabApiLcdDisplayLine ();

/*******************************************************************************
* Function    : CrabRegisterLcdApi
* Caption     : 注册LCD显示函数 
* Description : .
*******************************************************************************/
void CrabRegisterLcdApi()
{  
  CrabExtern_RegisterApi("LcdClear", CrabApiLcdClear);
  CrabExtern_RegisterApi("LcdClearLine", CrabApiLcdClearLine);
  CrabExtern_RegisterApi("LcdSetCursor", CrabApiLcdSetCursor);
  CrabExtern_RegisterApi("LcdSetScreen", CrabApiLcdSetScreen);
  CrabExtern_RegisterApi("LcdSetLight", CrabApiLcdSetLight);
  CrabExtern_RegisterApi("LcdDisplay", CrabApiLcdDisplay);
  CrabExtern_RegisterApi("LcdDisplayLine", CrabApiLcdDisplayLine);
}

/*******************************************************************************
* Function    : CrabApiLcdClear
* Caption     : LCD 清屏
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdClear ()
{
  LCD_Clear();
}

/*******************************************************************************
* Function    : CrabApiLcdClearLine
* Caption     : LCD 清除某一行
* Return      : crabapi
* Description : 如果行号为0，则清除当前行的当前位置至行尾
*******************************************************************************/
crabapi CrabApiLcdClearLine ()
{
  CrabUint Line;
    
  if (!CrabExtern_PopupParamAsUint(Line)) return;

  LCD_ClearLine(Line);
}

/*******************************************************************************
* Function    : CrabApiLcdSetCursor
* Caption     : LCD 设置光标是否显示
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdSetCursor ()
{
  CrabUint    Port = CrabExtern_GetPortAddr();
  CrabBool    ShowHide;
  
  if (!CrabExtern_ReadFromPortAsBool(ShowHide)) return;
  
  LCD_SetCursor(ShowHide);
}

/*******************************************************************************
* Function    : CrabApiLcdSetScreen
* Caption     : LCD 设置是否显示
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdSetScreen ()
{
  CrabUint    Port = CrabExtern_GetPortAddr();
  CrabBool    ShowHide;
  
  if (!CrabExtern_ReadFromPortAsBool(ShowHide)) return;
  
  LCD_SetScreen(ShowHide);
}

/*******************************************************************************
* Function    : CrabApiLcdSetLight
* Caption     : LCD 设置是否显示背光
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdSetLight ()
{
  CrabUint    Port = CrabExtern_GetPortAddr();
  CrabBool    ShowHide;
  
  if (!CrabExtern_ReadFromPortAsBool(ShowHide)) return;
  
  LCD_SetLight(ShowHide);
}
/*******************************************************************************
* Function    : CrabApiLcdDisplay
* Caption     : LCD 显示字符串
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdDisplay ()
{
  CrabUint     Line;
  CrabUint     Col;
  CrabString   Text; 

  if (!CrabExtern_PopupParamAsUint(Line)) return;
  if (!CrabExtern_PopupParamAsUint(Col)) return;
  if (!CrabExtern_PopupParamAsString(Text)) return;  
  
  if (Text == null) return;

  LCD_Display(Line, Col, Text->Data, false);
}

/*******************************************************************************
* Function    : CrabApiLcdDisplayLine
* Caption     : LCD 显示字符串，并清除行尾空白
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdDisplayLine ()
{
  CrabUint     Line;
  //CrabUint     Col;
  CrabString   Text; 

  if (!CrabExtern_PopupParamAsUint(Line)) return;
  //if (!CrabExtern_PopupParamAsUint(Col)) return;
  if (!CrabExtern_PopupParamAsString(Text)) return;  
  
  if (Text == null) return;

  LCD_Display(Line, 1, Text->Data, true);  
}