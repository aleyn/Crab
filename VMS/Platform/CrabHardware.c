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
const uint32_t TIM_ADDR[TIM_ADDR_MAX] = 
{ TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE, 
  TIM5_BASE, TIM6_BASE, TIM7_BASE, TIM8_BASE,
  TIM9_BASE, TIM10_BASE, TIM11_BASE, TIM12_BASE,
  TIM13_BASE, TIM14_BASE, 0, 0
};

const uint32_t TIM_RST[TIM_ADDR_MAX] = 
{
  RCC_APB2RSTR_TIM1RST, RCC_APB1RSTR_TIM2RST, RCC_APB1RSTR_TIM3RST, RCC_APB1RSTR_TIM4RST,
  RCC_APB1RSTR_TIM5RST, RCC_APB1RSTR_TIM6RST, RCC_APB1RSTR_TIM7RST, RCC_APB2RSTR_TIM8RST,
  RCC_APB2RSTR_TIM9RST, RCC_APB2RSTR_TIM10RST, RCC_APB2RSTR_TIM11RST, RCC_APB1RSTR_TIM12RST,
  RCC_APB1RSTR_TIM13RST, RCC_APB1RSTR_TIM14RST, 0, 0
};

const uint8_t TIM_APB[TIM_ADDR_MAX] = 
{
  0, 1, 1, 1,
  1, 0, 0, 0,
  2, 2, 2, 0,
  0, 0, 0, 0
};

const uint8_t TIM_AF[TIM_ADDR_MAX] = 
{
  GPIO_AF_TIM1, GPIO_AF_TIM2, GPIO_AF_TIM3, GPIO_AF_TIM4,
  GPIO_AF_TIM5, 0,            0,            GPIO_AF_TIM8,
  GPIO_AF_TIM9, GPIO_AF_TIM10, GPIO_AF_TIM11, GPIO_AF_TIM12,
  GPIO_AF_TIM13, GPIO_AF_TIM14, 0, 0
};

uint8_t KeyCount = 0;
uint8_t KeyBuffer[KEY_BUF_MAX] = {0};
uint8_t KeyRead = 0;
uint8_t KeyWrite = 0;
uint8_t KeyDown = 0;
uint8_t KeyDelay = 0xFF;

uint16_t BoardKey = 0;
uint16_t RemoteKey = 0;

uint32_t TIM_Period[TIM_ADDR_MAX];
CrabMotorDef CrabMotor[2];

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
  CrabHW_MotorControl(&CrabMotor[0], 0);

  CrabMotor[1].Active = 0;
  CrabHW_MotorControl(&CrabMotor[1], 0);
  
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
* Function    : CrabHW_BEEP_Enable
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Enable()
{
  if (BEP_IO)
  {
    CrabHW_TIM_Config(BEP_TIM, BEP_PULSE, BEP_SCALE);
  }
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Disable
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Disable()
{
  if (BEP_IO)
  {
    CrabHW_TIM_Config(BEP_TIM, 0, 0);
  }
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Start
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Start()
{
  if (BEP_IO)
  {
    CrabHW_TIM_SetPwmWithGPIO(BEP_TIM, BEP_CHANNEL, BEP_IO, BEP_WIDTH);
  }
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Stop
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Stop()
{
  if (BEP_IO)
  {
    CrabHW_TIM_SetPwmWithGPIO(BEP_TIM, BEP_CHANNEL, BEP_IO, 0);
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
* Function    : CrabHW_TIM_GetAddr
* Caption     : .
*  @Param     : 1.Index - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t CrabHW_TIM_GetAddr(uint8_t Index)
{
  if ((Index>0) && (Index <= TIM_ADDR_MAX))
  {
    return TIM_ADDR[Index - 1];
  }
  else
  {
    return 0;
  }
}

/*******************************************************************************
* Function    : CrabHW_TIM_Config
* Caption     : .
*  @Param     : 1.TIM - 
*  @Param     : 2.Period - 
*  @Param     : 3.Prescaler - 
* Description : .
*******************************************************************************/
void CrabHW_TIM_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  if (TIM == 0) return;
  TIM --;
  
  uint32_t ADDR = TIM_ADDR[TIM];
  uint32_t RST = TIM_RST[TIM];
  uint8_t  APB = TIM_APB[TIM];

  if ((ADDR == 0) || (RST == 0) || (APB == 0)) return;
  
  if (Period)
  {
    TIM_TimeBaseStructure.TIM_Period = Period;
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    if (APB == 1)
    {
      RCC_APB1PeriphClockCmd(RST, ENABLE);
    }
    else
    {
      RCC_APB2PeriphClockCmd(RST, ENABLE);
    }
    
    TIM_TimeBaseInit((TIM_TypeDef *) ADDR, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig((TIM_TypeDef *) ADDR, ENABLE);
    TIM_Cmd((TIM_TypeDef *) ADDR, ENABLE);        
  }
  else
  {
    TIM_ARRPreloadConfig((TIM_TypeDef *) ADDR, DISABLE);
    TIM_Cmd((TIM_TypeDef *) ADDR, DISABLE);
    
    if (APB == 1)
    {
      RCC_APB1PeriphClockCmd(RST, DISABLE);
    }
    else
    {
      RCC_APB2PeriphClockCmd(RST, DISABLE);
    }
  }
}

/*******************************************************************************
* Function    : CrabHW_TIM_SetPwm
* Caption     : .
*  @Param     : 1.TIM - 
*  @Param     : 2.OC - 
*  @Param     : 3.Value - 
* Description : .
*******************************************************************************/
void CrabHW_TIM_SetPwmWithGPIO(uint8_t TIM, uint8_t OC, uint32_t GIO, uint32_t Value)
{   
  if ((TIM == 0) || (GIO == 0)) return;
  TIM --;

  uint32_t ADDR = TIM_ADDR[TIM];
  uint8_t  AF  = TIM_AF[TIM];
  uint16_t OCE;
  
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  if (Value)
  {
    GPIO_InitPort(GIO, GPIO_MODE_PWM, AF);
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    OCE = TIM_OCPreload_Enable;
  }
  else
  {
    GPIO_InitPort(GIO, GPIO_MODE_PUT, 0);
    GPIO_SetBit(GIO, 0);
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    OCE = TIM_OCPreload_Disable;
  }
  
  switch (OC)
  {
    case 1:
    {
      TIM_OC1Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare1((TIM_TypeDef *) ADDR, Value);
      break;
    }
    case 2:
    {
      TIM_OC2Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare2((TIM_TypeDef *) ADDR, Value);
      break;
    }
    case 3:
    {
      TIM_OC3Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare3((TIM_TypeDef *) ADDR, Value);
      break;
    }
    case 4:
    {
      TIM_OC4Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC4PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare4((TIM_TypeDef *) ADDR, Value);
      break;
    }
  }
}

/*******************************************************************************
* Function    : CrabHW_MotorControl
* Caption     : 马达控制
* Return      : crabapi
* Description : .
*******************************************************************************/
void CrabHW_MotorControl(CrabMotorDef *Motor, uint8_t Reset)
{
  uint32_t Frequ;
  uint32_t Period;
  uint32_t Prescaler;
  
  if ((Motor->TIM == 0)) return;
  
  if (! Motor->Active)
  {
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->A_CH, Motor->A_IO, 0);
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->B_CH, Motor->B_IO, 0);
    CrabHW_TIM_Config(Motor->TIM, 0, 0);
    
    return;
  }
  
  if (Reset)
  {
    Frequ = Motor->Frequ;
    
    if (Frequ == 0)
    {
      Prescaler = 1;
      Period = 0;
    }
    else if (Frequ <= 10)
    {
      Prescaler = 10000;
      Period = 9600 / Frequ;
    }
    else if (Frequ <= 100)
    {
      Prescaler = 1000;
      Period = 96000 / Frequ;
    }
    else if (Frequ <= 1000)
    {
      Prescaler = 100;
      Period = 960000 / Frequ;
    }
    else if (Frequ <= 10000)
    {
      Prescaler = 10;
      Period = 9600000 / Frequ;
    }
    else
    {
      Prescaler = 1;
      Period = 96000000 / Frequ;
    }
    
    TIM_Period[Motor->TIM] = Period;
    CrabHW_TIM_Config(Motor->TIM, Period, Prescaler - 1);
  }
  else
  {
    Period = TIM_Period[Motor->TIM];
  }
  
  Prescaler = Period * (Motor->Speed) / 100;
  
  if (Motor->Polar == 0)
  {
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->B_CH, Motor->B_IO, 0);
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->A_CH, Motor->A_IO, Prescaler);
  }
  else
  {
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->A_CH, Motor->A_IO, 0);
    CrabHW_TIM_SetPwmWithGPIO(Motor->TIM, Motor->B_CH, Motor->B_IO, Prescaler);
  }
}