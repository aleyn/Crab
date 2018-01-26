/******************** Copyright forwise.com *********************************
* File Name         : stm32ext.c
* Author            : 吴创明(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2009-02-02
* Last Update       : 2017-07-18
* Description       : EXT firmware library.
********************************************************************************/
#include "stm32ext.h"

#define GPIO_PORT_ADDR(PortPin)  (uint32_t)((uint32_t)((PortPin >> 4) - 1) * (uint32_t)0x400 + GPIO_PORT_BASE)

#if defined (STM32F0)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)(GPIO_PORT_ADDR(PortPin) | AHB2PERIPH_BASE)
#elif defined (STM32F1)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)(GPIO_PORT_ADDR(PortPin) | APB2PERIPH_BASE)
#elif defined (STM32F4)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)(GPIO_PORT_ADDR(PortPin) | AHB1PERIPH_BASE)
#endif

#define GPIO_SETUP_MASK        0x000000FF

#if defined (STM32F1)
#define GPIO_SETUP_MODE(A)     (GPIOMode_Typedef) ((A >> 24) & GPIO_SETUP_MASK)
#define GPIO_SETUP_SPEED(B)    (GPIOSpeed_TypeDef)((B >> 16) & GPIO_SETUP_MASK)
#define GPIO_SETUP_OTYPE(C)    (GPIOOType_Typedef)((C >> 8)  & GPIO_SETUP_MASK)
#define GPIO_SETUP_PUPD(D)     (GPIOPuPd_Typedef) ((D     )  & GPIO_SETUP_MASK)
#else
#define GPIO_SETUP_MODE(A)     (GPIOMode_TypeDef) ((A >> 24) & GPIO_SETUP_MASK)
#define GPIO_SETUP_SPEED(B)    (GPIOSpeed_TypeDef)((B >> 16) & GPIO_SETUP_MASK)
#define GPIO_SETUP_OTYPE(C)    (GPIOOType_TypeDef)((C >> 8)  & GPIO_SETUP_MASK)
#define GPIO_SETUP_PUPD(D)     (GPIOPuPd_TypeDef) ((D     )  & GPIO_SETUP_MASK)
#endif
/*******************************************************************************
* Function    : GPIO_InitEx
* Caption     : GPIO 初始化
*  @Param     : 1.GPIOx - GPIO 端口号
*  @Param     : 2.GPIO_InitStruct - 
* Description : .
*******************************************************************************/
void GPIO_InitEx(GPIO_TypeDef* GPIOx, GPIO_InitExDef* GPIO_InitStruct)
{
#if defined (STM32F1)
  if (GPIO_InitStruct->GPIO_AlterFunc > 0)
  {
    GPIO_PinRemapConfig(GPIO_InitStruct->GPIO_AlterFunc, ENABLE);
  }
#else
  if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)
  {
    GPIO_PinAFConfig(GPIOx, GPIO_InitStruct->GPIO_PinSource, GPIO_InitStruct->GPIO_AlterFunc);
  }
#endif
  GPIO_Init(GPIOx, (GPIO_InitTypeDef *)GPIO_InitStruct);
}

/*******************************************************************************
* Function    : GPIO_InitPort
* Caption     : GPIO 引脚初始化
*  @Param     : 1.PortPin - 引脚号
*  @Param     : 2.Mode -    模式
*  @Param     : 3.GPIO_AF - 复用功能
* Description : .
*******************************************************************************/
void GPIO_InitPort(GPIO_PORT PortPin, GPIO_MODE Mode, GPIO_AF AlterFunc)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_TypeDef      *GPIOx = GPIO_DECLARE(PortPin);

#if defined (STM32F1)
  GPIOMode_TypeDef GPIO_Mode;
  GPIOOType_Typedef GPIO_OType = GPIO_SETUP_OTYPE(Mode);
    
  switch (GPIO_SETUP_MODE(Mode))
  {
    case GPIO_Mode_AN:
    {
      GPIO_Mode = GPIO_Mode_AIN;
      break;
    }
    case GPIO_Mode_IN:
    {
      GPIO_Mode = (GPIOMode_TypeDef)GPIO_SETUP_PUPD(Mode);
      break;
    }
    case GPIO_Mode_OUT:
    {
      GPIO_Mode = (GPIOMode_TypeDef)((uint8_t)GPIO_Mode_OUT | (uint8_t)GPIO_OType);
      break;
    }
    case GPIO_Mode_AF:
    {
      GPIO_Mode = (GPIOMode_TypeDef)((uint8_t)GPIO_Mode_AF | (uint8_t)GPIO_OType);           
      break;
    }
  }
  
  if (AlterFunc > 0)
  {
    GPIO_PinRemapConfig(AlterFunc, ENABLE);
  }
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
  GPIO_InitStructure.GPIO_Pin = GPIO_GETPIN(PortPin);
  GPIO_InitStructure.GPIO_Speed = GPIO_SETUP_SPEED(Mode);
  
#else
  GPIO_InitStructure.GPIO_Pin = GPIO_GETPIN(PortPin);
  GPIO_InitStructure.GPIO_Mode = GPIO_SETUP_MODE(Mode);
  GPIO_InitStructure.GPIO_Speed = GPIO_SETUP_SPEED(Mode);
  GPIO_InitStructure.GPIO_OType = GPIO_SETUP_OTYPE(Mode);
  GPIO_InitStructure.GPIO_PuPd = GPIO_SETUP_PUPD(Mode);

  if (GPIO_InitStructure.GPIO_Mode == GPIO_Mode_AF)
  {
    GPIO_PinAFConfig(GPIOx, GPIO_GETPIN_SRC(PortPin), AlterFunc);
  }
#endif
  
  GPIO_Init(GPIOx, &GPIO_InitStructure);  
}

/*******************************************************************************
* Function    : GPIO_GetBit
* Caption     : 读取IO引脚电平状态
*  @Param     : 1.PortPin - IO引脚
*  @Param     : 2.GpioMode - 读取模式
* Return      : uint8_t
* Description : .
*******************************************************************************/
uint8_t  GPIO_GetBit(GPIO_PORT PortPin, uint8_t InOut)
{
  GPIO_TypeDef      *GPIOx = GPIO_DECLARE(PortPin);
  uint16_t           Pin = GPIO_GETPIN(PortPin);
  
  if (InOut == GPIO_Mode_IN)
  {
    return GPIO_ReadInputDataBit(GPIOx, Pin);
  }
  else
  {
    return GPIO_ReadOutputDataBit(GPIOx, Pin);
  }
}

/*******************************************************************************
* Function    : GPIO_SetBit
* Caption     : 设置IO引脚电平状态
*  @Param     : 1.PortPin - IO引脚
*  @Param     : 2.BitValue - 新的电平状态
* Description : .
*******************************************************************************/
void GPIO_SetBit(GPIO_PORT PortPin, uint8_t BitValue)
{
  GPIO_TypeDef      *GPIOx = GPIO_DECLARE(PortPin);
  uint16_t           Pin = GPIO_GETPIN(PortPin);
  
  if (BitValue)
  {
    GPIO_SetBits(GPIOx, Pin);
  }
  else
  {
    GPIO_ResetBits(GPIOx, Pin);
  }
}

/*******************************************************************************
* Function    : GPIO_ToggleBit
* Caption     : 翻转IO引脚电平状态
*  @Param     : 1.PortPin - IO引脚
* Description : .
*******************************************************************************/
void GPIO_ToggleBit(GPIO_PORT PortPin)
{
  GPIO_TypeDef      *GPIOx = GPIO_DECLARE(PortPin);
  
#if defined (STM32F0) || defined(STM32F1)
  uint16_t           Pin = GPIO_GETPIN(PortPin);
  
  if (GPIO_ReadOutputDataBit(GPIOx, Pin))
  {
    GPIO_ResetBits(GPIOx, Pin);
  }
  else
  {
    GPIO_SetBits(GPIOx, Pin);
  }
  
#elif defined (STM32F4)
  GPIO_ToggleBits(GPIOx, GPIO_GETPIN(PortPin));
#endif
}

/*******************************************************************************
* Function    : GPIO_SetBit
* Caption     : 
*  @Param     : 1.PortPin - 
*  @Param     : 2.BitValue - 
* Description : .
*******************************************************************************/
int8_t   GPIO_GetState(GPIO_PORT PortPin)
{
  int8_t Result = GPIO_STATE_ZERO;
  
  GPIO_InitPort(PortPin, GPIO_MODE_INU, 0);
  
  if (GPIO_GetInputBit(PortPin) == 0)
  {
    Result = GPIO_STATE_LOW;
  }
  else
  {
    GPIO_InitPort(PortPin, GPIO_MODE_IND, 0);

    if (GPIO_GetInputBit(PortPin) == 1)
    {
      Result = GPIO_STATE_HIGH;
    }
  }
  
  return Result;
}

/*******************************************************************************
* Function    : GPIO_GetBitMap
* Caption     : .
*  @Param     : 1.PortPinMap - 
*  @Param     : 2.GpioMode - 
*  @Param     : 3.Count - 
* Return      : uint32_t
* Description : .
*******************************************************************************/
uint32_t GPIO_GetBitMap(GPIO_PORT *PortPinMap, uint8_t InOut, uint32_t Count)
{
  uint32_t Result = 0;
  uint32_t Last = 32 - Count;
  
  while (Count)
  {
    Result >>= 1;

    if (GPIO_GetBit(*PortPinMap, InOut))
    {
      Result |= 0x80000000;
    }

    PortPinMap++;
    Count--;
  }
  
  Result >>= Last;
  return Result;
}

/*******************************************************************************
* Function    : GPIO_SetBitMap
* Caption     : .
*  @Param     : 1.PortPinMap - 
*  @Param     : 2.BitMapValue - 
*  @Param     : 3.Count - 
* Description : .
*******************************************************************************/
void GPIO_SetBitMap(GPIO_PORT *PortPinMap, uint32_t BitMapValue, uint32_t Count)
{
  while (Count)
  {
    GPIO_SetBit(*PortPinMap, BitMapValue & 0x00000001);

    BitMapValue >>= 1;
    PortPinMap++;
    Count--;
  }
}

/*******************************************************************************
* Function    : EXTI_InitLine
* Caption     : .
*  @Param     : 1.PortPin - 
* Description : .
*******************************************************************************/
void EXTI_InitLine(GPIO_PORT PortPin)
{
#if defined (STM32F4)  
  uint16_t  Port = GPIO_GETPORT_SRC(PortPin);
#endif
  uint16_t  Pin = GPIO_GETPIN(PortPin);
  
  EXTI_InitTypeDef   EXTI_InitStructure;

#if defined (STM32F4)  
  SYSCFG_EXTILineConfig(Port, GPIO_GETPIN_SRC(PortPin));
#endif
  
  EXTI_InitStructure.EXTI_Line = Pin;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);  
}

/*******************************************************************************
* Function    : USART_InitEasy
* Caption     : USART 简易设置
*  @Param     : 1.USART - 串口号
*  @Param     : 2.BaudRate - 串口波率
* Description : .
*******************************************************************************/
void USART_InitEasy(USART_TypeDef *USART, uint32_t BaudRate)
{
  USART_InitTypeDef USART_InitStructure;
  
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure and enable the USART */
  USART_Init(USART, &USART_InitStructure);
  USART_Cmd(USART, ENABLE);
}

/*******************************************************************************
* Function    : LED_Output
* Caption     : LED 输出
*  @Param     : 1.LED_PIN - 引脚编号
*  @Param     : 2.Status -  新的输出状态
* Description : .
*******************************************************************************/
void LED_Output(GPIO_PORT LED_PIN, uint8_t Status)
{
  switch (Status)
  {
    case LED_OFF:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_GET, 0);
      break;
    }
    case LED_LOW:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_LED, 0);
      GPIO_SetBit(LED_PIN, 0);
      break;
    }
    case LED_HIGH:
    {
      GPIO_InitPort(LED_PIN, GPIO_MODE_LED, 0);
      GPIO_SetBit(LED_PIN, 1);
      break;
    }
  }
}

/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/