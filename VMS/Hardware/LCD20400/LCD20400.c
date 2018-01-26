/******************** Copyright wisearm.com *********************************
* File Name         : LCD20400.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-09-20
* Last Update       : 2017-09-20
* Description       : 实用单元
********************************************************************************/

#include "LCD20400.h"
#include "LCD20400CFG.h"
#include <stdio.h>
#include <stdlib.h>

I2C_Master_Def I2C_LCD20400;

void LCD_Config()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
  GPIO_InitPort(LCD_SCL, GPIO_MODE_I2C, GPIO_AF_I2C1);
  GPIO_InitPort(LCD_SDA, GPIO_MODE_I2C, GPIO_AF_I2C1);
 
  I2CM_DefaultSet(&I2C_LCD20400);
  
  I2C_LCD20400.I2C = LCD_I2C;
  I2C_LCD20400.DeviceAddr = LCD20400_DEVICE_ADDR;
  
  I2CM_Config(&I2C_LCD20400);
}

uint8_t  LCD_CheckBusy()
{
  uint8_t   Status = 0;
  uint32_t  Timeout = 100000;
  uint32_t  I;
  
  /* I2C Peripheral Enable */
  I2C_Cmd(I2C_LCD20400.I2C, ENABLE);
  I2C_AcknowledgeConfig(I2C_LCD20400.I2C, ENABLE); 
    
  do
  {
    if (I2CM_DirectRead(&I2C_LCD20400, &Status, 1) == I2CM_Timeout) break;
    if (Status == 0) break;
    
    for (I = 0; I < 100000; I++)
    {
      Status = 1;
    }
    
    Timeout --;
  } while (Status && Timeout);

  if ((Timeout == 0) || (Status))
  {
    I2C_Cmd(I2C_LCD20400.I2C, DISABLE);

    return 1;
  }
  else
  {
    return 0;
  }
}

void    LCD_Finally()
{
  I2C_Cmd(I2C_LCD20400.I2C, DISABLE);
  
  //GPIO_InitPort(LCD_SCL, GPIO_MODE_GET, 0);
  //GPIO_InitPort(LCD_SDA, GPIO_MODE_GET, 0);
}

void LCD_Help()
{
  if (LCD_CheckBusy()) return;
  
  I2CM_ByteWrite(&I2C_LCD20400, LCD_CMD_HELP, LCD_CMD_ADDR);
  LCD_Finally();
}

void LCD_Reset()
{
  if (LCD_CheckBusy()) return;

  I2CM_ByteWrite(&I2C_LCD20400, LCD_CMD_RESET, LCD_CMD_ADDR);
  LCD_Finally();
}

void LCD_Clear()
{
  TLCD_CmdAddr CmdAddr;
  if (LCD_CheckBusy()) return;

  CmdAddr.Command = LCD_CMD_CLEAR;
  CmdAddr.Addr = 0;
  
  I2CM_PageWrite(&I2C_LCD20400, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  LCD_Finally();
}

void LCD_SetCursor(uint8_t ShowHide)
{
  if (LCD_CheckBusy()) return;

  if (ShowHide)
  {
    I2CM_ByteWrite(&I2C_LCD20400, LCD_CMD_SHOWCURSOR, LCD_CMD_ADDR);
  }
  else
  {
    I2CM_ByteWrite(&I2C_LCD20400, LCD_CMD_HIDECURSOR, LCD_CMD_ADDR);
  }
  
  LCD_Finally();
}

void LCD_SetScreen(uint8_t ShowHide)
{
  if (LCD_CheckBusy()) return;

  if (ShowHide)
  {
  }
  else
  {
  }
  
  LCD_Finally();
}

void LCD_ClearLineToEnd(uint8_t Line, uint8_t Col)
{
  TLCD_CmdAddr CmdAddr;
  
  CmdAddr.Command = LCD_CMD_CLEAR;
  CmdAddr.Line = Line;
  CmdAddr.Col  = Col;
  
  if (LCD_CheckBusy()) return;

  I2CM_PageWrite(&I2C_LCD20400, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  LCD_Finally();
}

void LCD_Display(uint8_t Line, uint8_t Col, char *Text, uint8_t ClearToEnd)
{
  TLCD_CmdAddr CmdAddr;
  uint32_t I;
  
  CmdAddr.Line = Line;
  CmdAddr.Col  = Col;
  
  if (LCD_CheckBusy()) return;

  I2CM_PageWrite(&I2C_LCD20400, (uint8_t*)Text, CmdAddr.Addr, 0);
  LCD_Finally();
  
  if (ClearToEnd)
  {
    while (*Text)
    {
      Col++;
      Text++;
    }
    
    if (Col <= LCD_COL_MAX)
    {
      for (I=0;I<10000;I++);
      LCD_ClearLineToEnd(Line, Col);
    }

  }
}

/** @} */
