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

const uint32_t TIM_IO[TIM_ADDR_MAX*4] = 
{
  /*1*/ 0,        0,        0,        0,
  /*2*/ GPIO_PA5, GPIO_PA1, 0,        GPIO_PA3,
  /*3*/ GPIO_PA6, GPIO_PA7, GPIO_PB0, GPIO_PB1,
  /*4*/ 0,        0,        GPIO_PB8, GPIO_PB9,
  /*5*/ GPIO_PA0, GPIO_PA1, 0,        GPIO_PA3,
  /*6*/ 0,        0,        0,        0,
  /*7*/ 0,        0,        0,        0,
  /*8*/ 0,        0,        0,        0,
  /*9*/ GPIO_PA2, GPIO_PA3, 0,        0,
 /*10*/ GPIO_PB8, 0,        0,        0,
 /*11*/ GPIO_PB9, 0,        0,        0,
 /*12*/ 0,        0,        0,        0,
 /*13*/ 0,        0,        0,        0,
 /*14*/ 0,        0,        0,        0,
 /*15*/ 0,        0,        0,        0,
 /*16*/ 0,        0,        0,        0,
};

#define GPIO_ADDR_MAX 10
const uint32_t GPIO_ADDR[GPIO_ADDR_MAX] = 
{
  GPIO_PA0, GPIO_PA1, GPIO_PA3, GPIO_PA5,
  GPIO_PA6, GPIO_PA7, GPIO_PB0, GPIO_PB1,
  GPIO_PB8, GPIO_PB9
};

uint8_t KeyCount = 0;
uint8_t KeyBuffer[KEY_BUF_MAX] = {0};
uint8_t KeyRead = 0;
uint8_t KeyWrite = 0;
uint8_t KeyDown = 0;
uint8_t KeyDelay = 0xFF;


/*******************************************************************************
* Function    : fputc
* Caption     : 支援Printf的函数
*  @Param     : 1.ch - 
*  @Param     : 2.f - 
* Return      : int
* Description : .
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(PRINTF_COM, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(PRINTF_COM, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

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
uint32_t CrabHW_KEY_Scan()
{
  uint32_t Key = 0;
  
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
  
  if (Key)
  {
    if (KeyDown != Key)
    { 
      KeyDown = Key;
      Key |= 0x00000100;
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
      CrabHW_KEY_Write(KeyDown);
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
  CrabHW_TIM_Config(BEP_TIM, BEP_PULSE, BEP_SCALE);
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Disable
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Disable()
{
  CrabHW_TIM_Config(BEP_TIM, 0, 0);
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Start
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Start()
{
  CrabHW_TIM_SetPwm(BEP_TIM, BEP_CHANNEL, BEP_WIDTH);
}

/*******************************************************************************
* Function    : CrabHW_BEEP_Stop
* Caption     : .
* Description : .
*******************************************************************************/
void CrabHW_BEEP_Stop()
{
  CrabHW_TIM_SetPwm(BEP_TIM, BEP_CHANNEL, 0);
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
void CrabHW_TIM_SetPwm(uint8_t TIM, uint8_t OC, uint32_t Value)
{   
  if (TIM == 0) return;
  TIM --;
  
  uint32_t ADDR = TIM_ADDR[TIM];
  uint32_t GIO = TIM_IO[TIM * 4 + OC - 1];
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