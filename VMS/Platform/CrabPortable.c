/******************** Copyright wisearm.com *********************************
* File Name         : CrabPortable.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2016-12-31
* Description       : 应用
********************************************************************************/
#include "CrabVMS.h"

//extern uint16_t ADCValue[];

#define ADC_REF 0.666

uint32_t TIM_Period[TIM_ADDR_MAX];

crabapi CrabGetKey ();
crabapi CrabSetLED ();
crabapi CrabGetGPIO ();
crabapi CrabSetGPIO ();
crabapi CrabGetADC ();

crabapi CrabSetupPWM ();
crabapi CrabWritePWM ();

/*******************************************************************************
* Function    : CrabRegisterPortApi
* Caption     : 注册轻端口API函数 
* Description : .
*******************************************************************************/
void    CrabRegisterPortApi()
{
  CrabExtern_RegisterApi("GetKey", CrabGetKey);
  CrabExtern_RegisterApi("SetLED", CrabSetLED);
  CrabExtern_RegisterApi("GetGPIO", CrabGetGPIO);
  CrabExtern_RegisterApi("SetGPIO", CrabSetGPIO);

  CrabExtern_RegisterApi("SetPWM", CrabSetupPWM);
  CrabExtern_RegisterApi("SetPWMW", CrabWritePWM);
}

/*******************************************************************************
* Function    : CrabGetKey
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetKey()
{
  CrabUint Key = CrabHW_KEY_Read(); 
  CrabExtern_ReturnUintValue(Key);
}

/*******************************************************************************
* Function    : CrabSetLED
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetLED()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabUint gPort = 0;
  CrabUint nValue = CrabExtern_GetUintParam(1);
  
  switch (Port)
  {
    case 1:
    {
      gPort = LED_1;
      break;
    }
    case 2:
    {
      gPort = LED_2;
      break;
    }
  }

  if (gPort)
  {
    CrabHW_LED_Change(gPort, nValue);
  }

}

/*******************************************************************************
* Function    : CrabGetGPIO
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetGPIO()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabUint nValue = 0;   
  CrabUint gPort = CrabHW_GPIO_GetAddr(Port);

  if (gPort)
  {
    GPIO_InitPort(gPort, GPIO_MODE_GET, 0);
    nValue = GPIO_GetInputBit(gPort);
  }
  
  CrabExtern_ReturnUintValue(nValue);
}

/*******************************************************************************
* Function    : CrabSetGPIO
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabSetGPIO()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  CrabUint nValue = CrabExtern_GetUintParam(1);
  CrabUint gPort = CrabHW_GPIO_GetAddr(Port);

  if (gPort)
  {
    GPIO_InitPort(gPort, GPIO_MODE_PUT, 0);
    GPIO_SetBit(gPort, nValue);
  }  
}

/*******************************************************************************
* Function    : CrabGetADC
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabGetADC()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  uint32_t I;
  uint32_t nValue = 0;
  
  if (Port > 0)
  {
    I = Port - 1;
  }
  else
  {
    I = 0;
  }
  
  while (I<8)
  {
    nValue += ADCValue[I];
    I+=2;
  }
  
  nValue >>=2;
  if (Port == 1)
  {
    //Value = Value * 100 / 4096;
    nValue *= ADC_REF;
  }
  else
  {
    nValue *= ADC_REF;
  }
  
  CrabExtern_ReturnUintValue(nValue);
}

/*******************************************************************************
* Function    : CrabSetupPWM
* Caption     : .
* Description : .
*******************************************************************************/
crabapi CrabSetupPWM()
{
  CrabUint Port = CrabExtern_GetPortAddr();
  uint32_t Period;
  uint32_t Prescaler;  
  
  uint8_t TIM = (Port >> 4) & 0x000F;
  uint8_t Pin = Port & 0x000F;
  uint32_t nValue = CrabExtern_GetUintParam(1);
  
  if (Pin)
  {
    Period = TIM_Period[TIM];
    
    if (nValue < 100)
    {
      Prescaler = Period * nValue / 100;
    }
    else
    {
      Prescaler = Period;
    }
    
    CrabHW_TIM_SetPwm(TIM, Pin, Prescaler);
  }
  else
  {
    if (nValue == 0)
    {
      Prescaler = 1;
      Period = 0;
    }
    else if (nValue < 10)
    {
      Prescaler = 10000;
      Period = 9600 / nValue;
    }
    else if (nValue < 100)
    {
      Prescaler = 1000;
      Period = 96000 / nValue;
    }
    else if (nValue < 1000)
    {
      Prescaler = 100;
      Period = 960000 / nValue;
    }
    else if (nValue < 10000)
    {
      Prescaler = 10;
      Period = 9600000 / nValue;
    }
    else
    {
      Prescaler = 1;
      Period = 96000000 / nValue;
    }
    
    TIM_Period[TIM] = Period;
    CrabHW_TIM_Config(TIM, Period, Prescaler - 1);
  }
}

/*******************************************************************************
* Function    : CrabWritePWM
* Caption     : .
* Return      : crabapi
* Description : .
*******************************************************************************/
crabapi CrabWritePWM()
{  
  CrabUint Port = CrabExtern_GetPortAddr();
  uint32_t Period;
  uint32_t Prescaler;
  
  uint8_t PWM = (Port >> 4) & 0x000F;
  uint8_t Pin = Port & 0x000F;
  
  uint32_t TIM = CrabHW_TIM_GetAddr(PWM);
  Period = TIM_Period[TIM];
  
  uint32_t nValue = CrabExtern_GetUintParam(1);
  
  if (nValue < 100)
  {
    Prescaler = Period * nValue / 100;
  }
  else
  {
    Prescaler = Period;
  }  
  
  switch (Pin)
  {
    case 1:
    {
      TIM_SetCompare1((TIM_TypeDef *) TIM, Prescaler);
      break;
    }
    case 2:
    {
      TIM_SetCompare2((TIM_TypeDef *) TIM, Prescaler);
      break;
    }
    case 3:
    {
      TIM_SetCompare3((TIM_TypeDef *) TIM, Prescaler);
      break;
    }
    case 4:
    {
      TIM_SetCompare4((TIM_TypeDef *) TIM, Prescaler);
      break;
    }
  }
}