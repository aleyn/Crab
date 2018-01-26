/******************** Copyright wisearm.com *********************************
* File Name         : LCD20400.h
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-09-20
* Last Update       : 2017-09-20
* Description       : 实用单元
********************************************************************************/
#ifndef __LCD20400_H
#define __LCD20400_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include "Hardware.h"
#include "I2C_Master.h"
   
#pragma pack(1)
typedef union
{ 
  struct
  {
    uint8_t    Command;
    uint8_t    Col;
    uint8_t    Line;
  };
  struct
  {
    uint8_t    Res;
    uint16_t   Addr;
  };
  struct
  {
    uint8_t    Res2;
    uint8_t    ShowHide;
    uint8_t    Res3;
  }
} TLCD_CmdAddr;

extern I2C_Master_Def           I2C_LCD20400;

#define LCD_LINE_MAX            4
#define LCD_COL_MAX             20

#define LCD_CMD_ADDR            0xFFFF

#define LCD_CMD_HELP            'h'
#define LCD_CMD_RESET           'r'
#define LCD_CMD_SHOWCURSOR      's'
#define LCD_CMD_HIDECURSOR      'd'
#define LCD_CMD_CLEAR           'c'

#define LCD_ClearLine(a)                LCD_ClearLineToEnd(a, 1)
#define LCD_DisplayLine(Line, Text)     LCD_Display(Line, 1, Text, true) 

void LCD_Config();
uint8_t LCD_CheckBusy();
void    LCD_Finally();

void LCD_Help();
void LCD_Reset();
void LCD_Clear();
void LCD_SetCursor(uint8_t ShowHide);
void LCD_SetScreen(uint8_t ShowHide);
void LCD_ClearLineToEnd(uint8_t Line, uint8_t Col);
void LCD_Display(uint8_t Line, uint8_t Col, char *Text, uint8_t ClearToEnd);

#endif
/** @} */
