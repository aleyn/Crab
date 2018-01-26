/******************** Copyright wisearm.com *********************************
* File Name         : CrabHardware.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 硬件配置与设置
********************************************************************************/
#include "CrabVMS.h"
#include "CrabHardware.h"

/*******************************************************************************
* Description : 硬件地址配置
*******************************************************************************/

uint8_t KeyCount = 0;
uint8_t KeyBuffer[KEY_BUF_MAX] = {0};
uint8_t KeyRead = 0;
uint8_t KeyWrite = 0;
uint8_t KeyDown = 0;
uint8_t KeyDelay = 0xFF;

uint16_t BoardKey = 0;
uint16_t RemoteKey = 0;

uint32_t TIM_Period[TIM_ADDR_MAX];
CrabMotorDef CrabMotor[MOTOR_COUNT];

/*******************************************************************************
* Function    : CrabHW_InitExtern
* Caption     : 外部硬件初始化
* Description : .
*******************************************************************************/
void CrabHW_InitExtern()
{
  Device_Init(); 
}

/*******************************************************************************
* Function    : CrabHW_Reset
* Caption     : 硬件软复位
* Description : .
*******************************************************************************/
void CrabHW_Reset()
{
  KeyCount = 0;
  KeyRead = 0;
  KeyWrite = 0;
  BoardKey = 0;
  RemoteKey = 0;
  
  CrabHW_LED_Change(LED_1, LED_OFF);
  CrabHW_LED_Change(LED_2, LED_OFF);
  
  CrabMotor[0].TIM  = MOTO1_TIM;
  CrabMotor[0].A_CH = MOTO1_A_CH;
  CrabMotor[0].A_IO = MOTO1_A_IO;
  CrabMotor[0].B_CH = MOTO1_B_CH;
  CrabMotor[0].B_IO = MOTO1_B_IO;

  CrabMotor[1].TIM  = MOTO2_TIM;
  CrabMotor[1].A_CH = MOTO2_A_CH;
  CrabMotor[1].A_IO = MOTO2_A_IO;
  CrabMotor[1].B_CH = MOTO2_B_CH;
  CrabMotor[1].B_IO = MOTO2_B_IO;
  
  CrabMotor[0].Active = 0;
  //CrabHW_MotorControl(&CrabMotor[0], 0);

  CrabMotor[1].Active = 0;
  //CrabHW_MotorControl(&CrabMotor[1], 0);
  
}

/*******************************************************************************
* Function    : CrabHW_PutString
* Caption     : 输出字符串到标准设备
*  @Param     : 1.Data - 
*  @Param     : 2.Length - 
* Return      : int
* Description : .
*******************************************************************************/
void CrabHW_PutString(char *Data, uint32_t Length)
{
  while (Length)
  {
    putchar(*Data);
    Data++;
    Length--;
  }
}

/*******************************************************************************
* Function    : CrabHW_LED_Change
* Caption     : .
*  @Param     : 1.LED_PIN - 
*  @Param     : 2.Status - 
* Description : .
*******************************************************************************/
void CrabHW_LED_Change(uint32_t LED_PIN, uint8_t Status)
{  
  switch (Status)
  {
    case LED_OFF:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_GET, 0);
      break;
    }
    case LED_GREEN:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_LED, 0);
      GPIO_SetBit(LED_PIN, 0);
      break;
    }
    case LED_RED:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_LED, 0);
      GPIO_SetBit(LED_PIN, 1);
      break;
    }
  }
}

/*******************************************************************************
* Function    : CrabHW_KEY_Scan
* Caption     : .
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint16_t CrabHW_KEY_Scan()
{
  uint16_t Key = 0;
  
#if KEY_SCAN == 1
  GPIO_InitPort(KEY_1, GPIO_MODE_INU, 0);
  GPIO_InitPort(KEY_2, GPIO_MODE_INU, 0);

  if (GPIO_GetInputBit(KEY_1) == 0)
  {
    Key = 0x10;
  }
  
  if (GPIO_GetInputBit(KEY_2) == 0)
  {
    Key = 0x20;
  }
  
  GPIO_InitPort(KEY_1, GPIO_MODE_IND, 0);
  GPIO_InitPort(KEY_2, GPIO_MODE_IND, 0);

  if (GPIO_GetInputBit(KEY_1) == 1)
  {
    Key = 0x11;
  }  

  if (GPIO_GetInputBit(KEY_2) == 1)
  {
    Key = 0x21;
  }
#else
  GPIO_InitPort(KEY_1, GPIO_MODE_GET, 0);
  GPIO_InitPort(KEY_2, GPIO_MODE_GET, 0);

  if (GPIO_GetInputBit(KEY_1) == 0)
  {
    Key = 0x10;
  }
  
  if (GPIO_GetInputBit(KEY_2) == 0)
  {
    Key = 0x20;
  }
#endif
  
  if (Key)
  {
    if (KeyDown != Key)
    { 
      KeyDown = Key;
      Key |= 0x0100;
      KeyDelay = 10;
    }
    else
    {
      if (KeyDelay > 5) KeyDelay--;
      Key = 0;
    }
  }
  else if (KeyDown)
  {
    if (KeyDelay)
    {
      KeyDelay--;
      Key = 0;
    }
    else
    {
    #if KEY_BUFFER_MODE == 1
      CrabHW_KEY_Write(KeyDown);
    #endif
      Key = KeyDown;
      KeyDown = 0;
    }
  }
  
  return Key;
}

/*******************************************************************************
* Function    : CrabHW_KEY_Read
* Caption     : .
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t CrabHW_KEY_Read()
{
  uint8_t Result;
  
  if (KeyCount)
  {
    Result = KeyBuffer[KeyRead];
    
    KeyBuffer[KeyRead] = 0;
    KeyRead++;
    
    if (KeyRead >= KEY_BUF_MAX)
    {
      KeyRead = 0;
    }
    
    KeyCount --;
  }
  else
  {
    Result = 0;
  }
  
  return Result;
}

/*******************************************************************************
* Function    : CrabHW_KEY_Write
* Caption     : .
*  @Param     : 1.Key - 
* Description : .
*******************************************************************************/
void CrabHW_KEY_Write(uint8_t Key)
{
  KeyBuffer[KeyWrite] = Key;
  KeyWrite++;
  KeyCount++;

  if (KeyWrite >= KEY_BUF_MAX)
  {
    KeyWrite = 0;
  }
}

/*******************************************************************************
* Function    : CrabHW_GPIO_GetAddr
* Caption     : .
*  @Param     : 1.Index - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t CrabHW_GPIO_GetAddr(uint8_t Index)
{
  if ((Index>0) && (Index <= GPIO_ADDR_MAX))
  {
    return GPIO_ADDR[Index - 1];
  }
  else
  {
    return 0;
  }
}

/*******************************************************************************
* Function    : SECOND_IRQHandler
* Caption     : 秒信号定时器中断
* Description : 秒信号定时器
*******************************************************************************/
void SECOND_IRQHandler(void)
{
  //TIM_ClearFlag(SECOND_TIM, TIM_FLAG_CC1);
  //TIM_GetITStatus(SECOND_TIM, TIM_FLAG_Update);
  TIM_ClearFlag(SECOND_TIM, TIM_FLAG_Update);
  CrabAlarmSecondEvent();
}

/*******************************************************************************
* Function    : CrabSetupSecondEvent
* Caption     : 设置秒信号
*  @Param     : 1.Index - 新的信号状态开关
* Description : SECOND_TIM_IDX 是秒信号定时器
*******************************************************************************/
void CrabSetupSecondEvent(uint8_t Status)
{
  uint32_t Period;
  uint32_t Prescaler;
  
  if (Status)
  {
    Prescaler = 10000;
    Period = SystemCoreClock / Prescaler;
    
    PulseTimer_Config(SECOND_TIM_IDX, Period - SECOND_CALI, Prescaler - 1);
    PulseTimer_Interrupt(SECOND_TIM_IDX, CrabTrue);
  }
  else
  {
    PulseTimer_Config(SECOND_TIM_IDX, 0, 0);
    PulseTimer_Interrupt(SECOND_TIM_IDX, CrabFalse);
  }
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Enable
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Enable()
{
#ifdef BEP_IO
  PulseTimer_Config(BEP_TIM, BEP_PULSE, BEP_SCALE);
#endif
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Disable
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Disable()
{
#ifdef BEP_IO
  PulseTimer_Config(BEP_TIM, 0, 0);
#endif
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Start
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Start()
{
#ifdef BEP_IO
  GPIO_InitPort(BEP_IO, GPIO_MODE_PWM, BEP_AF); 
  PulseTimer_SetOutput(BEP_TIM, BEP_CHANNEL, BEP_WIDTH);
#endif
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Stop
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Stop()
{
#ifdef BEP_IO    
  GPIO_InitPort(BEP_IO, GPIO_MODE_PUT, 0);
  PulseTimer_SetOutput(BEP_TIM, BEP_CHANNEL, 0);
#endif
}