/******************** Copyright forwise.com *********************************
* File Name         : stm32ext.c
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2009-02-02
* Last Update       : 2012-08-05
* Description       : EXT firmware library.
********************************************************************************/
#include "stm32ext.h"

#if defined (STM32F0)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)((PortPin >> 16) | AHB2PERIPH_BASE)
#elif defined (STM32F1)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)((PortPin >> 16) | APB2PERIPH_BASE)
#elif defined (STM32F4)
  #define GPIO_DECLARE(PortPin)  (GPIO_TypeDef*)((PortPin >> 16) | AHB1PERIPH_BASE)
#endif

#define GPIO_GETPIN(PortPin)    (PortPin & GPIO_PIN_ALL)
#define GPIO_GETPORT(PortPin)   (PortPin >> 16)
#define GPIO_GETEXTI(PortPin)   (PortPin >> 26)

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
* Caption     : .
*  @Param     : 1.GPIOx - 
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
* Caption     : .
*  @Param     : 1.PortPin - 
*  @Param     : 2.Mode - 
*  @Param     : 3.GPIO_AF - 
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
    GPIO_PinAFConfig(GPIOx, GPIO_PortToSrc(PortPin), AlterFunc);
  }
#endif
  
  GPIO_Init(GPIOx, &GPIO_InitStructure);  
}

/*******************************************************************************
* Function    : GPIO_GetBit
* Caption     : .
*  @Param     : 1.PortPin - 
*  @Param     : 2.GpioMode - 
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
* Caption     : .
*  @Param     : 1.PortPin - 
*  @Param     : 2.BitValue - 
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
* Caption     : .
*  @Param     : 1.PortPin - 
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
* Function    : GPIO_PortToSrc
* Caption     : .
*  @Param     : 1.PortPin - 
* Description : .
*******************************************************************************/
uint32_t GPIO_PortToSrc(GPIO_PORT PortPin)
{
  uint16_t           Pin = GPIO_GETPIN(PortPin);
  uint32_t           Result = 0;
  
  switch (Pin)
  {
    case GPIO_PIN_0:
    {
      Result = GPIO_PinSource0;
      break;
    }
    case GPIO_PIN_1:
    {
      Result = GPIO_PinSource1;
      break;
    }
    case GPIO_PIN_2:
    {
      Result = GPIO_PinSource2;
      break;
    }
    case GPIO_PIN_3:
    {
      Result = GPIO_PinSource3;
      break;
    }
    case GPIO_PIN_4:
    {
      Result = GPIO_PinSource4;
      break;
    }
    case GPIO_PIN_5:
    {
      Result = GPIO_PinSource5;
      break;
    }
    case GPIO_PIN_6:
    {
      Result = GPIO_PinSource6;
      break;
    }
    case GPIO_PIN_7:
    {
      Result = GPIO_PinSource7;
      break;
    }
    case GPIO_PIN_8:
    {
      Result = GPIO_PinSource8;
      break;
    }
    case GPIO_PIN_9:
    {
      Result = GPIO_PinSource9;
      break;
    }
    case GPIO_PIN_10:
    {
      Result = GPIO_PinSource10;
      break;
    }
    case GPIO_PIN_11:
    {
      Result = GPIO_PinSource11;
      break;
    }
    case GPIO_PIN_12:
    {
      Result = GPIO_PinSource12;
      break;
    }
    case GPIO_PIN_13:
    {
      Result = GPIO_PinSource13;
      break;
    }
    case GPIO_PIN_14:
    {
      Result = GPIO_PinSource14;
      break;
    }
    case GPIO_PIN_15:
    {
      Result = GPIO_PinSource15;
      break;
    }
  }
  
  return Result;
}

void EXTI_InitLine(GPIO_PORT PortPin)
{
#if defined (STM32F4)  
  uint16_t  Port = GPIO_GETEXTI(PortPin);
#endif
  uint16_t  Pin = GPIO_GETPIN(PortPin);
  
  EXTI_InitTypeDef   EXTI_InitStructure;

#if defined (STM32F4)  
  SYSCFG_EXTILineConfig(Port, GPIO_PortToSrc(Pin));
#endif
  
  EXTI_InitStructure.EXTI_Line = Pin;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);  
}

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

void TurnLed(GPIO_PORT LED_PIN, uint8_t Status)
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