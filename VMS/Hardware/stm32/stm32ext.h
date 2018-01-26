/******************** Copyright wisearm.com *********************************
* File Name         : stm32ext.h
* Author            : Îâ´´Ã÷(aleyn.wu)
* Version           : V1.0.0
* Create Date       : 2009-02-02
* Last Update       : 2017-07-18
* Description       : EXT firmware library.
********************************************************************************/
#ifndef __STM32EXT_H
#define __STM32EXT_H

#if defined (STM32F0)
  #include "stm32f0xx.h"
#elif defined (STM32F1)
  #include "stm32f10x.h"
  #include "stm32f10x_gpio.h"
  #include "stm32f10x_usart.h"
  #include "stm32gpio.h"
#elif defined (STM32F4)
  #include "stm32f4xx.h"
#endif

#ifdef __cplusplus
 extern "C" {
#endif

typedef uint8_t   GPIO_PORT;
typedef uint32_t  GPIO_MODE;
typedef uint32_t  GPIO_AF;

#pragma pack(1)
typedef union
{
  struct
  {
    uint8_t Pin:4;
    uint8_t Port:4;
  };
  uint8_t   PortPin;
} TGPIO_PortPin, *PGPIO_PortPin;

#pragma pack(1)
typedef struct
{
#if defined (STM32F1)
  GPIO_InitTypeDef;
  uint32_t            GPIO_AlterFunc;
#else  
  GPIO_InitTypeDef;
  uint16_t            GPIO_PinSource;
  uint8_t             GPIO_AlterFunc;
#endif
} GPIO_InitExTypeDef, GPIO_InitExDef;
#pragma pack()

#define GPIO_PIN_EXT_MASK          (uint8_t)0x0F
#define GPIO_PIN_SET(Pin)          (uint8_t)Pin
#define GPIO_PORT_SET(Port)        (uint8_t)Port

/* ExPORTed constants --------------------------------------------------------*/
/* GPIO PINs define ----------------------------------------------------------*/
#include "stm32gpio_def.h"

#define GPIO_GETPORT(PortPin)       (uint8_t)((PortPin >> 4) - 1)
#define GPIO_GETPIN(PortPin)        (uint16_t)((uint16_t)1 << (PortPin & GPIO_PIN_EXT_MASK))
#define GPIO_GETPORT_SRC(PortPin)   (uint8_t)((PortPin >> 4) - 1)
#define GPIO_GETPIN_SRC(PortPin)    (uint8_t)(PortPin & GPIO_PIN_EXT_MASK)

#define GPIO_SETUP(A, B, C, D) (((uint32_t)A << 24) | ((uint32_t) B<< 16) | ((uint32_t)C << 8) | (uint32_t)D)

#define GPIO_NULL           0
#define GPIO_AF_NULL        0

#if defined (STM32F0)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_10MHz
  #define GPIO_Speed_High  GPIO_Speed_50MHz
#elif defined (STM32F1)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_10MHz
  #define GPIO_Speed_High  GPIO_Speed_50MHz
#elif defined (STM32F4)
  #define GPIO_Speed_Low   GPIO_Speed_2MHz
  #define GPIO_Speed_Mid   GPIO_Speed_50MHz
  #define GPIO_Speed_High  GPIO_Speed_100MHz
#endif

#define GPIO_STATE_ZERO   0
#define GPIO_STATE_LOW   -1
#define GPIO_STATE_HIGH   1


#include "stm32gpio_mode.h"

#define GPIO_GetInputBit(PortPin)                GPIO_GetBit(PortPin, GPIO_Mode_IN)
#define GPIO_GetOutputBit(PortPin)               GPIO_GetBit(PortPin, GPIO_Mode_OUT)
#define GPIO_GetInputBitMap(PortPin, Count)      GPIO_GetBitMap(PortPin, GPIO_Mode_IN,  Count)
#define GPIO_GetOutputBitMap(PortPin, Count)     GPIO_GetBitMap(PortPin, GPIO_Mode_OUT, Count)

void     GPIO_InitEx(GPIO_TypeDef* GPIOx, GPIO_InitExDef* GPIO_InitStruct);
void     GPIO_InitPort(GPIO_PORT PortPin, GPIO_MODE Mode, GPIO_AF AlterFunc);

uint8_t  GPIO_GetBit(GPIO_PORT PortPin, uint8_t InOut);
void     GPIO_SetBit(GPIO_PORT PortPin, uint8_t BitValue);
void     GPIO_ToggleBit(GPIO_PORT PortPin);
int8_t   GPIO_GetState(GPIO_PORT PortPin);

uint32_t GPIO_GetBitMap(GPIO_PORT *PortPinMap, uint8_t InOut, uint32_t Count);
void     GPIO_SetBitMap(GPIO_PORT *PortPinMap, uint32_t BitMapValue, uint32_t Count);

void     EXTI_InitLine(GPIO_PORT PortPin);

#if defined (STM32F0)
  #define SPI_SendData(a, b)      SPI_SendData8(a, b)
  #define SPI_ReceiveData(a)      SPI_ReceiveData8(a)
  #define SPI_GetStatus(a, b)     SPI_I2S_GetFlagStatus(a, b)
#elif defined (STM32F1)
  #define SPI_SendData(a, b)      SPI_I2S_SendData(a, b)
  #define SPI_ReceiveData(a)      SPI_I2S_ReceiveData(a)
  #define SPI_GetStatus(a, b)     SPI_I2S_GetFlagStatus(a, b)
#elif defined (STM32F4)
  #if !defined(SPI_SendData)
    #define SPI_SendData(a, b)      SPI_I2S_SendData(a, b)
  #endif
  #if !defined(SPI_ReceiveData)
    #define SPI_ReceiveData(a)      SPI_I2S_ReceiveData(a)
  #endif
  #define SPI_GetStatus(a, b)     SPI_GetFlagStatus(a, b)
#endif

void USART_InitEasy(USART_TypeDef *USART, uint32_t BaudRate);

#define  LED_OFF   0
#define  LED_ON    1
#define  LED_LOW   1
#define  LED_HIGH  2
#define  LED_GREEN 1
#define  LED_BLUE  1
#define  LED_RED   2
#define  TurnLed(a,b)  LED_Output(a,b)
#define  TurnLED(a,b)  LED_Output(a,b)

void LED_Output(GPIO_PORT LED_PIN, uint8_t Status);

#ifdef __cplusplus
}
#endif
#endif 
/*******************************************************************************
**                                END OF FILE                                 **
*******************************************************************************/
