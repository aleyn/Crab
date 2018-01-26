/******************** Copyright wisearm.com *********************************
* File Name         : CrabLCD.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2017-09-20
* Last Update       : 2017-09-20
* Description       : 实用单元
********************************************************************************/

#include "CrabLCD.h"
#include "CrabLCDCFG.h"
#include <stdio.h>
#include <stdlib.h>
#include <CrabVMS.h>

#define CrabLCD_Log(FMT, ...)  custom_log2("CrabLCD", FMT, ##__VA_ARGS__)

#define           CrabLCD_Task_Name            (TASK_NAME)"CrabLCD"
#define           CrabLCD_Task_Level           TASK_PRIO(4)
#define           CrabLCD_Task_Size            128
#define           CrabLCD_Task_Param           NULL
TASK_HANDLE 	    CrabLCD_Task_Object;

#define LCD_ACT_HELP              1 
#define LCD_ACT_RESET             2
#define LCD_ACT_CLEAR             3
#define LCD_ACT_SETCURSOR         4
#define LCD_ACT_SETSCREEN         5
#define LCD_ACT_SETLIGHT          6
#define LCD_ACT_CLEARLINETOEND    7
#define LCD_ACT_DISPLAY           8

I2C_Master_Def I2C_LCD;

uint32_t I2C_LCD_ResetCount = 0;

typedef struct
{
  uint8_t Action;
  uint8_t Line;
  uint8_t Col;
  char*   Text;
  union
  {
    uint8_t ClearToEnd;
    uint8_t ShowHide;
  };
} I2C_LCD_ACT_DEF;

I2C_LCD_ACT_DEF  LCD_Action = {0};

void LCD_GpioInit()
{
  GPIO_InitPort(LCD_SCL, GPIO_MODE_I2C, GPIO_AF_I2C1);
  GPIO_InitPort(LCD_SDA, GPIO_MODE_I2C, GPIO_AF_I2C1);
  
}

void LCD_GpioDeInit()
{
  GPIO_InitPort(LCD_SCL, GPIO_MODE_PUT, 0);
  GPIO_InitPort(LCD_SDA, GPIO_MODE_PUT, 0);
  
  GPIO_SetBit(LCD_SCL, 1);
  GPIO_SetBit(LCD_SDA, 1);
}

void LCD_Config()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
  GPIO_InitPort(LCD_SCL, GPIO_MODE_I2C, GPIO_AF_I2C1);
  GPIO_InitPort(LCD_SDA, GPIO_MODE_I2C, GPIO_AF_I2C1);
 
  I2CM_DefaultSet(&I2C_LCD);
  
  I2C_LCD.I2C = LCD_I2C;
  I2C_LCD.DeviceAddr = CRABLCD_DEVICE_ADDR;
  I2C_LCD.GpioInit = LCD_GpioInit;
  I2C_LCD.GpioDeInit = LCD_GpioDeInit;
      
  I2CM_Config(&I2C_LCD);
  
  LCD_Action.Action = 0;
  
}

uint8_t  LCD_CheckBusy()
{
  uint8_t   Status = 0;
  uint32_t  Timeout = 10000;
  uint32_t  I;
    
  do
  {
    if (I2CM_DirectRead(&I2C_LCD, &Status, 1) == I2CM_Timeout)
    {
      I2C_LCD_ResetCount++;
      printf("I2CM Timeout, reset(%d)\r\n", I2C_LCD_ResetCount);
      I2CM_Reset(&I2C_LCD);
      Status = 1;
    }
    
    if (Status == 0) break;
    
    for (I = 0; I < 1000000; I++)
    {
      Status = 1;
    }
    
    Timeout --;
  } while (Status && Timeout);

  if ((Timeout == 0) || (Status))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void LCD_Inner_Help()
{
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;
    
    I2CM_ByteWrite(&I2C_LCD, LCD_CMD_HELP, LCD_CMD_ADDR);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}

void LCD_Help()
{
  LCD_Action.Action = LCD_ACT_HELP;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_Reset()
{
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;

    I2CM_ByteWrite(&I2C_LCD, LCD_CMD_RESET, LCD_CMD_ADDR);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}

void LCD_Reset()
{
  LCD_Action.Action = LCD_ACT_RESET;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_Clear()
{
  TLCD_CmdAddr CmdAddr;
  
  CmdAddr.Command = LCD_CMD_CLEAR;
  CmdAddr.Addr = 0;
  
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;
    
    I2CM_PageWrite(&I2C_LCD, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_Clear()
{
  LCD_Action.Action = LCD_ACT_CLEAR;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_SetCursor(uint8_t ShowHide)
{
  TLCD_CmdAddr CmdAddr;
  
  CmdAddr.Command = LCD_CMD_CURSOR;
  CmdAddr.ShowHide  = ShowHide;
  
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;

    I2CM_PageWrite(&I2C_LCD, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_SetCursor(uint8_t ShowHide)
{
  LCD_Action.Action = LCD_ACT_SETCURSOR;
  LCD_Action.ShowHide = ShowHide;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_SetScreen(uint8_t ShowHide)
{
  TLCD_CmdAddr CmdAddr;
  
  //CmdAddr.Command = LCD_CMD_LIGHT;
  CmdAddr.ShowHide  = ShowHide;

  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;
  
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_SetScreen(uint8_t ShowHide)
{
  LCD_Action.Action = LCD_ACT_SETSCREEN;
  LCD_Action.ShowHide = ShowHide;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_SetLight(uint8_t ShowHide)
{
  TLCD_CmdAddr CmdAddr;
  
  CmdAddr.Command = LCD_CMD_LIGHT;
  CmdAddr.ShowHide  = ShowHide;
  
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;

    I2CM_PageWrite(&I2C_LCD, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_SetLight(uint8_t ShowHide)
{
  LCD_Action.Action = LCD_ACT_SETLIGHT;
  LCD_Action.ShowHide = ShowHide;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_ClearLineToEnd(uint8_t Line, uint8_t Col)
{
  TLCD_CmdAddr CmdAddr;
  
  CmdAddr.Command = LCD_CMD_CLEAR;
  CmdAddr.Line = Line;
  CmdAddr.Col  = Col;
  
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;

    I2CM_PageWrite(&I2C_LCD, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_ClearLineToEnd(uint8_t Line, uint8_t Col)
{
  LCD_Action.Action = LCD_ACT_CLEARLINETOEND;
  LCD_Action.Line = Line;
  LCD_Action.Col = Col;
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void LCD_Inner_Display(uint8_t Line, uint8_t Col, char *Text, uint8_t ClearToEnd)
{
  TLCD_CmdAddr CmdAddr;
  uint32_t I;
  
  CmdAddr.Line = Line;
  CmdAddr.Col  = Col;
  
  I2CM_Start(&I2C_LCD);

  do
  {
    if (LCD_CheckBusy()) break;

    I2CM_PageWrite(&I2C_LCD, (uint8_t*)Text, CmdAddr.Addr, 0);
  
    if (!ClearToEnd) break;

    while (*Text)
    {
      Col++;
      Text++;
    }
      
    if (Col > LCD_COL_MAX) break;

    for (I=0; I<10000; I++);
        
    CmdAddr.Command = LCD_CMD_CLEAR;
    CmdAddr.Line = Line;
    CmdAddr.Col  = Col;
    
    if (LCD_CheckBusy()) break;

    I2CM_PageWrite(&I2C_LCD, (uint8_t*)&CmdAddr, LCD_CMD_ADDR, 3);
  } while(0);
  
  I2CM_Stop(&I2C_LCD);
}
void LCD_Display(uint8_t Line, uint8_t Col, char *Text, uint8_t ClearToEnd)
{
  LCD_Action.Action = LCD_ACT_DISPLAY;
  LCD_Action.Line = Line;
  LCD_Action.Col = Col;
  LCD_Action.Text = Text;
  LCD_Action.ClearToEnd = ClearToEnd;
  
  //EXTI_GenerateSWInterrupt(LCD_EXTI);
  vTaskResume(CrabLCD_Task_Object);
}

void CrabLCD_Task(void *parg)
{
  
  for(;;)
  {
    switch (LCD_Action.Action)
    {
      case LCD_ACT_HELP:
      {
        LCD_Inner_Help();
        break;
      }    
      case LCD_ACT_RESET:
      {
        LCD_Inner_Reset();
        break;
      }    
      case LCD_ACT_CLEAR:
      {
        LCD_Inner_Clear();
        break;
      }    
      case LCD_ACT_SETCURSOR:
      {
        LCD_Inner_SetCursor(LCD_Action.ShowHide);
        break;
      }    
      case LCD_ACT_SETSCREEN:
      {
        LCD_Inner_SetScreen(LCD_Action.ShowHide);
        break;
      }    
      case LCD_ACT_SETLIGHT:
      {
        LCD_Inner_SetLight(LCD_Action.ShowHide);
        break;
      }    
      case LCD_ACT_CLEARLINETOEND:
      {
        LCD_Inner_ClearLineToEnd(LCD_Action.Line, LCD_Action.Col);
        break;
      }    
      case LCD_ACT_DISPLAY:
      {
        LCD_Inner_Display(LCD_Action.Line, LCD_Action.Col, LCD_Action.Text, LCD_Action.ClearToEnd);
        break;
      }    
    }
    
    vTaskSuspend(CrabLCD_Task_Object);
  }
  
  vTaskDelete( NULL );  
}

void LCD_CreateTask()
{
    xTaskCreate(CrabLCD_Task,
                CrabLCD_Task_Name,
                CrabLCD_Task_Size,
                CrabLCD_Task_Param,
                CrabLCD_Task_Level,
               &CrabLCD_Task_Object);
}

/** @} */
