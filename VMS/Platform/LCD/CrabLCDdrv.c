/******************** Copyright wisearm.com *********************************
* File Name         : CrabLCD.c
* Author            : �ⴴ��(aleyn.wu)
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
* Caption     : ע��LCD��ʾ���� 
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
* Caption     : LCD ����
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabApiLcdClear ()
{
  LCD_Clear();
}

/*******************************************************************************
* Function    : CrabApiLcdClearLine
* Caption     : LCD ���ĳһ��
* Return      : crabapi
* Description : ����к�Ϊ0���������ǰ�еĵ�ǰλ������β
*******************************************************************************/
crabapi CrabApiLcdClearLine ()
{
  CrabUint Line;
    
  if (!CrabExtern_PopupParamAsUint(Line)) return;

  LCD_ClearLine(Line);
}

/*******************************************************************************
* Function    : CrabApiLcdSetCursor
* Caption     : LCD ���ù���Ƿ���ʾ
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
* Caption     : LCD �����Ƿ���ʾ
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
* Caption     : LCD �����Ƿ���ʾ����
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
* Caption     : LCD ��ʾ�ַ���
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
* Caption     : LCD ��ʾ�ַ������������β�հ�
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