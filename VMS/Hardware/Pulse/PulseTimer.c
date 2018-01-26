/******************** Copyright wisearm.com *********************************
* File Name         : PulseTimer.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2012-06-15
* Last Update       : 2017-07-19
* Description       : 定时脉冲控制
********************************************************************************/
#include "PulseTimer.h"

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
  1, 1, 1, 0,
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

uint32_t  TIM_FREQU[TIM_ADDR_MAX] = {0};

/*******************************************************************************
* Function    : PulseTimer_GetAddr
* Caption     : 取得定时脉冲频率
*  @Param     : 1.Index - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t PulseTimer_GetFrequ(uint8_t Index)
{
  if ((Index>0) && (Index <= TIM_ADDR_MAX))
  {
    return TIM_FREQU[Index - 1];
  }
  else
  {
    return 0;
  }
}

/*******************************************************************************
* Function    : PulseTimer_Config
* Caption     : 定时脉冲配置
*  @Param     : 1.TIM - 
*  @Param     : 2.Period - 
*  @Param     : 3.Prescaler - 
* Description : .
*******************************************************************************/
void PulseTimer_Config(uint8_t TIM, uint32_t Period, uint32_t Prescaler)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  if ((TIM == 0 ) && (TIM > TIM_ADDR_MAX)) return;
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
* Function    : PulseTimer_ConfigAsFrequ
* Caption     : 定时脉冲配置，频率方式
*  @Param     : 1.TIM - 
*  @Param     : 2.Frequ - 频率: 0 - 100000
* Description : .
*******************************************************************************/
uint32_t  PulseTimer_ConfigEx(uint8_t TIM, uint32_t Frequ)
{
  uint32_t Period;
  uint32_t Prescaler;
  
  if ((TIM == 0 ) && (TIM > TIM_ADDR_MAX)) return 0;
  
  if (Frequ == 0)
  {
    Prescaler = 1;
  }
  else if (Frequ <= 10)
  {
    Prescaler = 10000;
  }
  else if (Frequ <= 100)
  {
    Prescaler = 1000;
  }
  else if (Frequ <= 1000)
  {
    Prescaler = 100;
  }
  else if (Frequ <= 10000)
  {
    Prescaler = 10;
  }
  else
  {
    Prescaler = 1;
  }
  
  if (Frequ == 0)
  {
    Period = 0;
  }
  else
  {
    Period = SystemCoreClock / Prescaler / Frequ;
  }
  
  if (TIM)
  {
    PulseTimer_Config(TIM, Period, Prescaler - 1);
    TIM_FREQU[TIM - 1 ] = Frequ;
  }

  return Period;
}

/*******************************************************************************
* Function    : PulseTimer_CalcWidth
* Caption     : 计算定时脉冲宽度
*  @Param     : 1.Period - 频率: 0 - 100000
*  @Param     : 2.Speed - 速度与极性:
*                      0: 关闭
*                1 ~ 100: 正向速度
*             -1 ~ - 100: 反向速度
* Description : .
*******************************************************************************/
uint32_t  PulseTimer_CalcWidth(uint32_t Period, int8_t Speed)
{
  if (Speed < 0)
  {
    Speed = -Speed;
  }
  
  return (Period * Speed / 100);
}

/*******************************************************************************
* Function    : PulseTimer_SetOutput
* Caption     : 定时脉冲输出
*  @Param     : 1.TIM - 
*  @Param     : 2.OC - 
*  @Param     : 3.Width - 
* Description : .
*******************************************************************************/
void PulseTimer_SetOutput(uint8_t TIM, uint8_t OC, uint32_t Width)
{ 
  if (TIM == 0) return;
  TIM --;

  uint32_t ADDR = TIM_ADDR[TIM];
  uint16_t OCE;
  
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  if (Width)
  {
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //TIM_OCInitStructure.TIM_Pulse = Width;
    OCE = TIM_OCPreload_Enable;
  }
  else
  {
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    //TIM_OCInitStructure.TIM_Pulse = 0;
    OCE = TIM_OCPreload_Disable;
  }
  
  switch (OC)
  {
    case 1:
    {
      TIM_OC1Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare1((TIM_TypeDef *) ADDR, Width);
      break;
    }
    case 2:
    {
      TIM_OC2Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare2((TIM_TypeDef *) ADDR, Width);
      break;
    }
    case 3:
    {
      TIM_OC3Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare3((TIM_TypeDef *) ADDR, Width);
      break;
    }
    case 4:
    {
      TIM_OC4Init((TIM_TypeDef *) ADDR, &TIM_OCInitStructure);
      TIM_OC4PreloadConfig((TIM_TypeDef *) ADDR, OCE);
      TIM_SetCompare4((TIM_TypeDef *) ADDR, Width);
      break;
    }
  }
}

/*******************************************************************************
* Function    : PulseTimer_Interrupt
* Caption     : 定时脉冲中断
*  @Param     : 1.TIM - 
*  @Param     : 2.Status - 
* Description : .
*******************************************************************************/
void PulseTimer_Interrupt(uint8_t TIM, uint8_t Status)
{
  if (TIM == 0) return;
  TIM --;

  uint32_t ADDR = TIM_ADDR[TIM];
  
  TIM_ClearFlag((TIM_TypeDef *) ADDR, TIM_FLAG_Update);
  
  //TIM_UpdateRequestConfig((TIM_TypeDef *) ADDR, TIM_UpdateSource_Global);
  //TIM_UpdateDisableConfig((TIM_TypeDef *) ADDR, Status);
  
  TIM_ITConfig((TIM_TypeDef *) ADDR, TIM_IT_Update, Status);
}